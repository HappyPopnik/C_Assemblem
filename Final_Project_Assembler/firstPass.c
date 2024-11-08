#include <stdio.h>
#include "firstPass.h"
#include "utilities.h"
#include "operations.h"
#include "secondPass.h"
#include "errors.h"

void symbolExists(SymbolList* head, const char* name, int line_num) {
	SymbolList* current = head;
	while (current != NULL) {
		if (strcmp(current->label, name) == 0) {
			printError(SYMBOL_ALREADY_EXISTS, line_num, current_processed_file);
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
	if (data_type == EXTERNAL)
	{
		newSymbol->externs_count = 0; /* Initialize extern count */
		newSymbol->extern_placements = malloc(sizeof(int) * (newSymbol->externs_count));
	}
		
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

void checkMemorySize(int ic, int dc, int line_num)
{
	if (ic + dc >= MAX_MEMORY_SIZE)
	{
		printError(EXCEEDED_MEMORY_LIMIT, line_num, current_processed_file);
	}
}

void jumpSpaceSepatation(char** line_pos, int line_number)
{
	if (**line_pos == ' ') /*Check for the space separation*/
	{
		(*line_pos)++;
	}
	else
	{
		printError(NO_SPACE_SEPARATION, line_number, current_processed_file);
	}
	while (*line_pos == ' ')
	{
		line_pos++;
	}
}

void increaseDataSymbolsByIC(SymbolList *symbols, int ic)
{
	SymbolList* current = symbols;
	while (current != NULL)
	{
		if (current->data_type == DATA  || current->data_type == STRING)
		{
			current->dc = current->dc + ic + 101;
		}
		current = current->next;
	}
}

void startFirstPass(FILE* sourcefp, char *filename)
{
	int data_type = 0;
	int ic, dc = 0;
	int asciichar;
	int line_number = 0;
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
		checkMemorySize(data_array->size, instruction_array->size, line_number);
		line_number++;
		char* trimmedLine = trimWhiteSpaceFromStart(line);
		if (isComment(trimmedLine) || isNewLine(line)) /* If it is a command line or nothing at all*/
			continue;
		char* colon_pos = strchr(line, ':');
		char* start_pos = line;
		removeNewLine(start_pos);
		if (colon_pos != NULL) { /*There is a label*/
			is_symbol_flag = 1;
			size_t label_length = colon_pos - line;
			/* Check if the label exceeds the maximum length */
			if (label_length > MAX_LABEL_LENGTH) {
				printError(LABEL_LENGTH_EXCEEDED, line_number, current_processed_file);
			}
			if (colon_pos == 0)
			{
				printError(LABEL_NOT_FOUND, line_number, current_processed_file);
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
				parseNumbers(start_pos, numbersdataarray, &numbersdatacount, line_number);
				iterating_index = 0;
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
				jumpSpaceSepatation(&start_pos, line_number);
				if (*start_pos == '\"') {
					start_pos++;
					char* end_quote = strchr(start_pos, '"');
					if (end_quote == NULL)
					{
						printError(MISSING_QUOTES, line_number, current_processed_file);
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
					printError(MISSING_QUOTES, line_number, current_processed_file);
				}
			}
			else if (strncmp(start_pos, ".extern", 7) == 0)
			{
				data_type = EXTERNAL;
				start_pos = start_pos + 7;
				jumpSpaceSepatation(&start_pos, line_number);
				char* label_ptr = label;
				int count = 0;
				int spacecount = 0;
				while (*start_pos != '\0') {
					if (*start_pos == ' ')
					{
						*start_pos++;
						continue;
					}
					*label_ptr++ = *start_pos++;
					count++;
				}
				label_ptr = label_ptr - spacecount;
				*label_ptr = '\0'; /*Add null terminator instead of \n*/
				label_ptr = label_ptr - count;
				symbolExists(extern_symbols, label_ptr, line_number); /*Check if the new symbol already exists*/
				addSymbolToTable(&extern_symbols, label_ptr, 0, data_type); /*Add the symbol to the symbol table*/
			}
			else if (strncmp(start_pos, ".entry", 6) == 0)
			{
				data_type = ENTRY;
				start_pos = start_pos + 6;
				jumpSpaceSepatation(&start_pos, line_number);
				char* label_ptr = label;
				int count = 0;
				while (*start_pos != '\0') {
					if (*start_pos == ' ')
					{
						*start_pos++;
						continue;
					}
					*label_ptr++ = *start_pos++;
					count++;
				}
				*label_ptr = '\0'; /* Add null terminator instead of \n */
				label_ptr = label_ptr - count;
				symbolExists(entry_symbols, label_ptr, line_number); /*Check if the new symbol already exists*/
				addSymbolToTable(&entry_symbols, label_ptr, 0, data_type); /*Add the symbol to the symbol table*/
			}
			if (is_symbol_flag && (data_type == DATA || data_type == STRING))
			{
				symbolExists(data_symbols, label, line_number); /*Check if the new symbol already exists*/
				addSymbolToTable(&data_symbols, label, dc, data_type); /*Add the symbol to the symbol table*/
			}
		}
		else /* '.' not found - command line*/
		{
			char* start_pos = line;
			start_pos = trimWhiteSpaceFromStart(line);
			trimTrailingSpaces(start_pos);
			ic = instruction_array->size;
			if (is_symbol_flag) /* Command and with label */
			{
				data_type = CODE;
				symbolExists(data_symbols, label, line_number);
				addSymbolToTable(&data_symbols, label, ic + 100, data_type);
				start_pos = colon_pos + 1;
				jumpSpaceSepatation(&start_pos, line_number);
			}
			int operation_index = operationExistsInOParray(start_pos);
			if (operation_index == 0)
			{
				printError(INVALID_OPERATION, line_number, current_processed_file);
			}
			else
			{
				Word* words_to_mem;
				int amount;
				words_to_mem = MakeWord(start_pos, operation_index, &amount, line_number);
				int L = amount;
				while (amount > 0)
				{
					moveToMem = *words_to_mem;
					words_to_mem++;
					amount--;
					addWord(instruction_array, moveToMem);
				}
			}
		}
	}
	increaseDataSymbolsByIC(data_symbols, ic);

	/* Finish first pass, moving to second pass */
	startSecondPass(data_symbols, entry_symbols, extern_symbols, data_array, instruction_array, filename);
	
}