#include <stdio.h>
#include "operations.h"
#include "errors.h"

int operationExistsInOParray(char* operation_name) {
    for (size_t i = 0; i <= NUM_OF_OPERATIONS; i++) {
        if (strncmp(operation_name, operations[i].operation_name, sizeof(operations[i].operation_name) -1) == 0) {
            return i;
        }
    }
    return 0;
}

int checkDeliveryOpt(int operation_index, int delivery_opt, int direction)
{
    /*check if in is in int array*/
    if (direction == DESTINATION_DIRECTION)
    {
        int *dest_arr = operations[operation_index].possible_dest_delivery_opts;
        for (int i = 0; i < sizeof(operations[operation_index].possible_dest_delivery_opts); i++) 
        {
            if (*dest_arr == delivery_opt) {
                return 1;
            }
            dest_arr = dest_arr + 1;
        }
    }
    else if (direction == SOURCE_DIRECTION)
    {
        int *source_arr = operations[operation_index].possible_src_delivery_opts;
        for (int i = 0; i < sizeof(operations[operation_index].possible_src_delivery_opts); i++) 
        {
            if (*source_arr == delivery_opt) {
                return 1;
            }
            source_arr = source_arr + 1;
        }
    }
    return 0;
    
}

int getAddressingOption(char *position)
{
    if (*position == '#')
    {
        return IMMIDIATE_ADDRESSING;
    }
    else if (*position == '*')
    {
        for (int i = 0; i < NUM_OF_REGISTERS; i++)
        {
            if (strncmp(position + 1, registries[i].registry_name, 2) == 0)
            {
                return INDIRECT_REG_ADDRESSING;
            }
        }
        printf("Invalid Register name!");
        exit(1);
        
    }
    else
    {
        for (int i = 0; i < NUM_OF_REGISTERS; i++)
        {
            if (strncmp(position, registries[i].registry_name, 2) == 0)
            {
                return DIRECT_REG_ADDRESSING;
            }
        }
        return DIRECT_ADDRESSING;
    }
}

int formatDirectOperandToInt(char* position)
{
    const char* start = position;
    while (*start && *start != ',') start++;
    size_t length = start - position;
    char* number_str = malloc(length + 1);
    strncpy(number_str, position, length);
    number_str[length] = '\0';
    char* endptr;
    long number = strtol(number_str, &endptr, 10);
    free(number_str);
    if (*endptr != '\0' && !(*endptr))
    {
        printf("Error in number conversion.");
        exit(1);
    }
    return number;
}

int getIntRegFromOperand(char *pos)
{
    pos++; /*Skipping the 'r' (we already did the valid input check)*/
    char chrnum = *pos;
    int number = chrnum - '0';
    return number;
}

int operandIncoding(int delivery_opt, char *pos, int is_dest)
{
    int word_encoding = 0;
    if (delivery_opt == IMMIDIATE_ADDRESSING)
    {
        pos++;
        int value = formatDirectOperandToInt(pos);
        if(is_dest)
            word_encoding = word_encoding + (value << 3);
        else
            word_encoding = word_encoding + (value << 6);
        word_encoding = word_encoding + A_FLAG;
    }
    else if ((delivery_opt == INDIRECT_REG_ADDRESSING) || (delivery_opt == DIRECT_REG_ADDRESSING))
    {
        int regnum = getIntRegFromOperand(pos);
        if (is_dest)
            word_encoding = word_encoding + (regnum << 3);
        else
            word_encoding = word_encoding + (regnum << 6);
        word_encoding = word_encoding + A_FLAG;
    }
    /* We will do DIRECT_ADDRESSING at second pass. */
    return word_encoding;
}

Word* MakeWord(char* pos, int operation_index, int *size, int line_num)
{
    char* temp = pos;
    Word instruction_word;
    Word dest_word;
    Word src_word;
    Word* word_list = malloc(3*sizeof(Word));
    Word* word_list_position = word_list;
    int word_encoding = 0;
    int src_opt, dest_opt;
    char* operation = operations[operation_index].operation_name;
    int expected_args = operations[operation_index].arguments;
    pos = pos + sizeof(operations[operation_index].operation_name);
    int op_code = operations[operation_index].op_code;
    op_code = op_code << 11; /* Adjust opcode to 14-11 bits */
    word_encoding = word_encoding + op_code;
    int delivery_opt;
    /*A is always 1 in command, R&E are 0*/
    word_encoding = word_encoding + A_FLAG;

    /* Check for addressing encoding and ensure the addressing is legal */
    if (expected_args == 0)
    {
        *size = 1;
        instruction_word.bits = word_encoding;
        *word_list = instruction_word;
    }
    else if (expected_args == 1)
    {
        *size = 2;
        if (containsCommaOrSpace(pos))
        {
            print_error(TWO_ARGUMENTS_INSTEAD_OF_ONE, line_num, current_processed_file);
        }
        else
        {
            delivery_opt = getAddressingOption(pos);
            /* Check if the delivery opt is allowed */
            if (checkDeliveryOpt(operation_index, delivery_opt, DESTINATION_DIRECTION))
            {
                /* Setting delivering for destination operand */
                word_encoding = word_encoding + (1 << (3 + delivery_opt));
                instruction_word.bits = word_encoding;
                /* Append the instruction word */
                *word_list = instruction_word;
                word_encoding = 0;
                /* Now encode the next word. */
                int is_dest = 1;
                word_encoding = operandIncoding(delivery_opt, pos, is_dest);
                if (delivery_opt == DIRECT_ADDRESSING)
                {
                    char* label = malloc(strlen(pos));
                    char* orig_label = label;
                    while (*pos != '\0' && *pos != ',' && *pos != ' ') {
                        *label++ = *pos++;
                    }
                    *label = '\0';
                    label = orig_label;
                    dest_word.symb_name = label;
                    printf("1");
                }
                dest_word.bits = word_encoding;
                word_list_position++;
                *word_list_position = dest_word;
            }
            else
            {
                printf("Illegal delivering option!");
                exit(1);
            }
        }
    }
    else if (expected_args == 2)
    {
        
        /*
            Already checked arguments not to exceed 2.
            So Just check if it contains a comma to separate them.
        */
        if (!containsCommaOrSpace(pos))
        {
            printf("Need more than one argument for this operation!");
            exit(1);
        }
        else
        {
            int src_delivery_opt;
            int dest_delivery_opt;
            char *start_of_operand_2 = pos;
            while (*start_of_operand_2 != ',') { 
                start_of_operand_2++;  
            }
            start_of_operand_2++;
            while (*start_of_operand_2 == ' ')
            {
                start_of_operand_2++;
            }
            src_delivery_opt = getAddressingOption(pos);
            dest_delivery_opt = getAddressingOption(start_of_operand_2);
            if (checkDeliveryOpt(operation_index, dest_delivery_opt, DESTINATION_DIRECTION) && \
                checkDeliveryOpt(operation_index, src_delivery_opt, SOURCE_DIRECTION))
            {
                word_encoding = word_encoding + (1 << (3 + dest_delivery_opt));
                word_encoding = word_encoding + (1 << (7 + src_delivery_opt));
                instruction_word.bits = word_encoding;
                /* Append the instruction word */
                *word_list = instruction_word;
                word_encoding = 0;
                if ((src_delivery_opt == INDIRECT_REG_ADDRESSING\
                    || src_delivery_opt == DIRECT_REG_ADDRESSING)\
                    && (dest_delivery_opt == INDIRECT_REG_ADDRESSING\
                        || dest_delivery_opt == DIRECT_REG_ADDRESSING))
                {
                    *size = 2;
                    /* In this case the next word will contain both registries */
                    word_encoding = word_encoding + A_FLAG;
                    int regnum_src = getIntRegFromOperand(pos);
                    int regnum_dst = getIntRegFromOperand(start_of_operand_2);
                    word_encoding = word_encoding + (regnum_dst << 3);
                    word_encoding = word_encoding + (regnum_src << 6);
                    dest_word.bits = word_encoding;
                    word_list_position++;
                    *word_list_position = dest_word;
                }
                else {
                    *size = 3;
                    int is_dest = 0;
                    word_encoding = operandIncoding(src_delivery_opt, pos, is_dest);
                    src_word.bits = word_encoding;
                    if (src_delivery_opt == DIRECT_ADDRESSING)
                    {
                        char* label = malloc(strlen(pos));
                        char* orig_label = label;
                        int count = 0;
                        while (*pos != '\0' && *pos != ',' && *pos != ' ') {
                            *label++ = *pos++;
                        }
                        *label = '\0';
                        label = orig_label;
                        src_word.symb_name = label;
                        printf("1");
                    }
                    word_list_position++;
                    *word_list_position = src_word;
                    word_encoding = 0;
                    is_dest = 1;
                    word_encoding = operandIncoding(dest_delivery_opt, start_of_operand_2, is_dest);
                    dest_word.bits = word_encoding;
                    if (dest_delivery_opt == DIRECT_ADDRESSING)
                    {
                        char *label = malloc(strlen(start_of_operand_2)+1);
                        char *orig_label = label;
                        int count = 0;
                        while (*start_of_operand_2 != '\0' ) {
                            *label++ = *start_of_operand_2++;
                            count++;
                        }
                        *label = '\0';
                        label = orig_label;
                        dest_word.symb_name = label;
                        printf("1");
                    }
                    word_list_position++;
                    *word_list_position = dest_word;
                }
            }
            else
            {
                printf("Wrong type of delivering method!");
                exit(1);
            }
        }
    }
    else
    {
        printf("Too many arguemnt!");
        exit(1);
    }

    Word* p = word_list;
    /*
    int size_of_words = *size;
    while (size_of_words > 0)
    {
        printf("%d\n", p->bits);
        p++;
        size_of_words--;
    }
    return word_list;
    */
}