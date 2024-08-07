#include <stdio.h>
#include "firstPass.h"
#include "utilities.h"
#include "memory_structs.h"
#include "operations.h"

void symbolExists(SymbolList* head, const char* name) {
	SymbolList* current = head;
	while (current != NULL) {
		if (strcmp(current->label, name) == 0) {
			printf("Error: Symbol with name '%s' already exists.\n", name);
			exit(1);
		}
		current = current->next;
	}
}

void addSymbolToTable(SymbolList** head, char* label, int dc, int data_type)
{
	SymbolList* newSymbol = (SymbolList*)malloc(sizeof(SymbolList));
	newSymbol->label = strdup(label);
	newSymbol->dc = dc;
	newSymbol->data_type = data_type;
	newSymbol->next = NULL;
	if (*head == NULL)
	{
		*head = newSymbol;
	}
	else
	{
		SymbolList* current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newSymbol;
	}
}

void checkMemorySize(int ic, int dc)
{
	if (ic + dc >= MAX_MEMORY_SIZE)
	{
		printf("Exceeded memory limit");
		exit(1);
	}
}

void jumpSpaceSepatation(char** line_pos)
{
	if (**line_pos == ' ') /*Check for the space separation*/
	{
		(*line_pos)++;
	}
	else
	{
		printf("No space separation.");
		exit(1);
	}
	while (*line_pos == ' ')
	{
		line_pos++;
	}
}

/*To delete*/
void printLinkedList(SymbolList* head) {
	SymbolList* current = head;
	while (current != NULL) {
		printf("label: %s\n", current->label);
		printf("dc: %d\n", current->dc);
		printf("data_type: %d\n", current->data_type);
		printf("------------\n");
		current = current->next;
	}
}

void printWordArray(MemoryArray* wordArray) {
	for (int i = 0; i < wordArray->size; ++i) {
		printf("Word %d: bits = %d, mem_res = %d, location = %p\n",
			i, wordArray->marray[i].bits, i, (void*)&wordArray->marray[i]);
	}
}

void startFirstPass(FILE* sourcefp)
{
	int data_type = 0;
	int ic, dc = 0;
	int asciichar;
	size_t iterating_index = 0;
	MemoryArray *data_array = createMemoryArray();
	MemoryArray *instruction_array = createMemoryArray();
	SymbolList* data_symbols = NULL;
	SymbolList* extern_symbols = NULL;
	SymbolList* entry_symbols = NULL;
	int is_symbol_flag = 0;
	char line[MAX_LINE_LENGTH];
	char label[MAX_LABEL_LENGTH];
	char string_content[MAX_LINE_LENGTH];
	int ascii_fixed_array[MAX_LINE_LENGTH];
	int numbersdataarray[MAX_LINE_LENGTH];
	int numbersdatacount = 0;
	Word moveToMem;
	while (fgets(line, sizeof(line), sourcefp) != NULL)
	{
		checkMemorySize(data_array->size, instruction_array->size);
		char* trimmedLine = trimWhiteSpaceFromStart(line);
		if (isComment(trimmedLine))
			continue;
		char* colon_pos = strchr(line, ':');
		char* start_pos = line;
		if (colon_pos != NULL) { /*There is a label*/
			is_symbol_flag = 1;
			size_t label_length = colon_pos - line;
			/* Check if the label exceeds the maximum length */
			if (label_length > MAX_LABEL_LENGTH) {
				printf("Error: Label name too long.");
				exit(1);
			}
			if (colon_pos == 0)
			{
				printf("Error: No name present but colon.");
				exit(1);
			}
			strncpy(label, line, label_length);
			label[label_length] = '\0';
			start_pos = colon_pos + 1; /*Move after the colon*/
		}
		else
		{
			/* No label, set label to an empty string */
			is_symbol_flag = 0;
		}
		if (strchr(line, '.')) /* Contains a operation to data*/
		{
			while (*start_pos == ' ') /*Get to the important stuff*/
			{
				start_pos++;
			}
			dc = data_array->size;
			if (strncmp(start_pos, ".data", 5) == 0)
			{
				data_type = DATA;
				start_pos = start_pos + 5;
				parse_numbers(start_pos, numbersdataarray, &numbersdatacount);
				iterating_index = 0;
				//for (int i = 0; i < sizeof(numbersdataarray); i++) {
				//	printf("%d\n", numbersdataarray[i]);
				//}
				for (int i = 0; i < numbersdatacount; i++)
				{
					moveToMem.bits = numbersdataarray[iterating_index];
					addWord(data_array, moveToMem);
					iterating_index++;
				}

			}
			else if (strncmp(start_pos, ".string", 7) == 0)
			{
				data_type = STRING;
				start_pos = start_pos + 7;
				jumpSpaceSepatation(&start_pos);
				if (*start_pos == '\"') {
					start_pos++;
					char* end_quote = strchr(start_pos, '"');
					if (end_quote == NULL)
					{
						printf("Error. No quotes found at end of string declaration.");
						exit(1);
					}
					else
					{
						size_t string_length = end_quote - start_pos;
						strncpy(string_content, start_pos, string_length);
						string_content[string_length] = '\0';
						iterating_index = 0;
						while (string_content[iterating_index] != '\0') {
							ascii_fixed_array[iterating_index] = (int)string_content[iterating_index];
							iterating_index++;
						}
						ascii_fixed_array[iterating_index] = 0;
						iterating_index = 0;
						while (ascii_fixed_array[iterating_index] != NULL)
						{
							moveToMem.bits = ascii_fixed_array[iterating_index];
							addWord(data_array, moveToMem);
							iterating_index++;
						}
						moveToMem.bits = 0;
						addWord(data_array, moveToMem); /*Add 0 to mark end of string*/
					}
				}
				else
				{
					printf("Error. No quotes found after string declaration.");
					exit(1);
				}
			}
			else if (strncmp(start_pos, ".extern", 7) == 0)
			{
				data_type = EXTERNAL;
				start_pos = start_pos + 7;
				jumpSpaceSepatation(&start_pos);
				char* label_ptr = label;
				while (*start_pos != '\0') {
					*label_ptr++ = *start_pos++;
				}
				*(label_ptr - 1) = '\0'; /*Add null terminator instead of \n*/
				symbolExists(data_symbols, label); /*Check if the new symbol already exists*/
				addSymbolToTable(&extern_symbols, label, 0, data_type); /*Add the symbol to the symbol table*/
			}
			else if (strncmp(start_pos, ".entry", 6) == 0)
			{
				data_type = ENTRY;
				start_pos = start_pos + 6;
				jumpSpaceSepatation(&start_pos);
				char* label_ptr = label;
				while (*start_pos != '\0') {
					*label_ptr++ = *start_pos++;
				}
				*(label_ptr - 1) = '\0'; /*Add null terminator instead of \n*/
				symbolExists(entry_symbols, label); /*Check if the new symbol already exists*/
				addSymbolToTable(&entry_symbols, label, 0, data_type); /*Add the symbol to the symbol table*/
			}
			if (is_symbol_flag && (data_type == DATA || data_type == STRING))
			{
				symbolExists(data_symbols, label); /*Check if the new symbol already exists*/
				addSymbolToTable(&data_symbols, label, dc, data_type); /*Add the symbol to the symbol table*/
			}
		}
		else /* '.' not found - command line*/
		{
			char* start_pos = line;
			ic = instruction_array->size;
			if (is_symbol_flag) /* Command and with label */
			{
				data_type = CODE;
				symbolExists(data_symbols, label);
				addSymbolToTable(&data_symbols, label, ic+100, data_type);
				start_pos = colon_pos + 1;
				jumpSpaceSepatation(&start_pos);
				int operation_index = operationExistsInOParray(start_pos);
				if (operation_index == 0)
				{
					printf("Invalid operation");
					exit(1);
				}
				else
				{
					int expected_args = operations[operation_index].arguments;
					start_pos = start_pos + sizeof(operations[operation_index].operation_name);
					
				}
			}
			

		}
	}
	printf("**********************\n");
	printLinkedList(data_symbols);
	printf("**********************\n");
	printLinkedList(entry_symbols);
	printf("**********************\n");
	printLinkedList(extern_symbols);
	printf("**********************\n");
	printWordArray(data_array);
	printf("**********************\n");
	
}