#include "utilities.h"
#include "memory_structs.h"

/* Specifications of the operations and registers */
#define NUM_OF_OPERATIONS 16

#define NUM_OF_REGISTERS 8

/* Addressing methods */
#define IMMIDIATE_ADDRESSING 0

#define DIRECT_ADDRESSING 1

#define INDIRECT_REG_ADDRESSING 2

#define DIRECT_REG_ADDRESSING 3

/* A,R,E flags in 2,1,0 bits */
#define A_FLAG 4

#define R_FLAG 2

#define E_FLAG 1

/* symbolization of direction of operand */
#define SOURCE_DIRECTION 1

#define DESTINATION_DIRECTION 2


/* operation struct, for the following operations table */
typedef struct operation {
    const char* operation_name;    
    int arguments;     /* How many arguments the opperation takes */
    int op_code;    /* The operation op_code (from 1 to 16) */
    int possible_src_delivery_opts[4]; /* list of legal src delivery options */
    int possible_dest_delivery_opts[4]; /* list of legal dest delivery options */
} operation;

/* registry struct for the 8 registers */
typedef struct registry {
    const char* registry_name;
    int registry_code;
} registry;

/* Opetarions table */
static operation operations[] = {
        {"INVALID", 0, 0,  {NULL},     NULL},
        {"mov",     2, 0,  {0,1,2,3},  {1,2,3}},
        {"cmp",     2, 1,  {0,1,2,3},  {0,1,2,3}},
        {"add",     2, 2,  {0,1,2,3},  {1,2,3}},
        {"sub",     2, 3,  {0,1,2,3},  {1,2,3}},
        {"lea",     2, 4,  {1},        {1,2,3}},
        {"clr",     1, 5,  {NULL},     {1,2,3}},
        {"not",     1, 6,  {NULL},     {1,2,3}},
        {"inc",     1, 7,  {NULL},     {1,2,3}},
        {"dec",     1, 8,  {NULL},     {1,2,3}},
        {"jmp",     1, 9,  {NULL},     {1,2}},
        {"bne",     1, 10, {NULL},     {1,2}},
        {"red",     1, 11, {NULL},     {1,2,3}},
        {"prn",     1, 12, {NULL},     {0,1,2,3}},
        {"jsr",     1, 13, {NULL},     {1,2}},
        {"rts",     0, 14, {NULL},     NULL},
        {"stop",    0, 15, {NULL},     NULL}
};
 /* Registries table */
static registry registries[] = {
    {"r0", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4},
    {"r5", 5},
    {"r6", 6},
    {"r7", 7}
};

int operationExistsInOParray(char* operation_name);
/*
   @ Function: operationExistsInOParray(char* operation_name)
   @ Arguments:
       - operation_name: A string representing the operation name to check.
   @ Description:
        Checks if an operation name exists in the operations table.
        Returns the index of the operation if found, otherwise returns 0.
*/

int checkDeliveryOpt(int operation_index, int delivery_opt, int direction);
/*
   @ Function: checkDeliveryOpt(int operation_index, int delivery_opt, int direction)
   @ Arguments:
       - operation_index: The index of the operation in the operations array.
       - delivery_opt: The delivery option to check.
       - direction: The direction to check (SOURCE_DIRECTION or DESTINATION_DIRECTION).
   @ Description:
        Checks if the given delivery option is valid for the specified direction of the given operation.
        Returns 1 if valid, else 0.
*/

int getAddressingOption(char* position, int line_num);
/*
   @ Function: getAddressingOption
   @ Arguments:
       - position: A string representing the operand.
       - line_num: The line number in the source file where the operand is located.
   @ Description:
        Finds the addressing method of the operand.
        Returns the addressing method as an integer value.
*/

int formatDirectOperandToInt(char* position, int line);
/*
   @ Function: formatDirectOperandToInt(char* position, int line
   @ Arguments:
       - position: A string representing the operand.
       - line: The line number in the source file where the operand is located.
   @ Description:
        Converts an operand from its string representation to an integer.
        Returns the integer value of the operand.
*/

int getIntRegFromOperand(char* pos);
/*
   @ Function: getIntRegFromOperand(char* pos)
   @ Arguments:
       - pos: A string representing the register operand.
   @ Description:
        Extracts the integer value of a register from its string representation.
        Returns the integer register number.
*/

int operandIncoding(int delivery_opt, char* pos, int is_dest, int line_num);
/*
   @ Function: operandIncoding(int delivery_opt, char* pos, int is_dest, int line_num)
   @ Arguments:
       - delivery_opt: The addressing method of the operand.
       - pos: A string representing the operand to be encoded.
       - is_dest: A flag indicating if the operand is a destination or source.
       - line_num: The line number in the source file where the operand is located.
   @ Description:
        Encodes an operand based on its addressing method and position.
        Returns the encoded word as an integer.
*/

Word* MakeWord(char* pos, int operation_index, int* size, int line_num);
/*
   @ Function: MakeWord(char* pos, int operation_index, int* size, int line_num)
   @ Arguments:
       - operation_index: The index of the operation in the operations table.
       - pos: A string representing the operand to be encoded.
       - size: An integer determing how many words the convertion would make.
       - line_num: The line number in the source file where the operand is located.
   @ Description:
        Encodes the line given into 1-3 words to the memory to be saved in first pass.
*/