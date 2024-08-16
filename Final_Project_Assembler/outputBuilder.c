#include <stdio.h>
#include "outputBuilder.h"
#include "utilities.h"
#include "errors.h"

#pragma warning(disable : 4996)

void makeObjectFile(FILE* file, MemoryArray* data_array, MemoryArray* instruction_array)
{
	fprintf(file, "%d %d\n", instruction_array->size, data_array->size);
	int i;
	for (i=0; i < instruction_array->size; i++)
	{
		char octalist[6];
		intToOctalString(instruction_array->marray[i].bits, octalist);
		fprintf(file, "%04d %s\n", i + 100, octalist);
	}
	for (int j = 0; j < data_array->size; j++)
	{
		char octalist[6];
		intToOctalString(data_array->marray[j].bits, octalist);
		fprintf(file, "%04d %s\n", i + 100, octalist);
		i++;
	}
	fclose(file);
}

void makeEntriesFile(FILE* file, SymbolList* entry_symbols)
{
	SymbolList *entry_current = entry_symbols;
	while (entry_current != NULL)
	{
		char* label = entry_current->label;
		int mem_res = entry_current->dc;
		fprintf(file, "%s %d\n", label, mem_res);
		entry_current = entry_current->next;
	}
	fclose(file);
}

void makeExternsFile(FILE* file, SymbolList* extern_symbols)
{
	SymbolList* extern_current = extern_symbols;
	while (extern_current != NULL)
	{
		char* label = extern_current->label;
		for (int i = 0; i < extern_current->externs_count; i++)
		{
			int line = extern_current->extern_placements[i];
			fprintf(file, "%s\t%04d\n", label, line);
		}
		
		extern_current = extern_current->next;
	}
	fclose(file);
}



void makeOutputFiles(SymbolList* data_symbols, SymbolList* entry_symbols,
	SymbolList* extern_symbols, MemoryArray* data_array, MemoryArray* instruction_array, char* filename)
{

	char object_filename[MAX_FILE_NAME_LENGTH];
	object_filename[0] = '\0';
	
	strcpy(object_filename, filename);

	strcat(object_filename, ".ob");

	FILE* object_file = fopen(object_filename, "w");
	if (object_file == NULL) {
		print_external_error(FILE_NOT_OPEN, current_processed_file, object_filename);
	}
	makeObjectFile(object_file, data_array, instruction_array);

	if (entry_symbols != NULL)
	{
		char entries_filename[MAX_FILE_NAME_LENGTH];
		entries_filename[0] = '\0';
		strcpy(entries_filename, filename);
		strcat(entries_filename, ".ent");
		FILE* entries_file = fopen(entries_filename, "w");
		if (entries_file == NULL) {
			print_external_error(FILE_NOT_OPEN, current_processed_file, entries_filename);
		}
		makeEntriesFile(entries_file, entry_symbols);
	}
	
	if (extern_symbols != NULL)
	{
		char extensions_filename[MAX_FILE_NAME_LENGTH];
		extensions_filename[0] = '\0';
		strcpy(extensions_filename, filename);
		strcat(extensions_filename, ".ext");
		FILE* extension_file = fopen(extensions_filename, "w");
		if (extension_file == NULL) {
			print_external_error(FILE_NOT_OPEN, current_processed_file, extensions_filename);
		}
		makeExternsFile(extension_file, extern_symbols);
	}


}