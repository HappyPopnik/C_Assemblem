#include <stdio.h>
#include "outputBuilder.h"
#include "utilities.h"

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

void makeEntriesFile(FILE* file, SymbolList* entry_symbols, SymbolList* data_symbols)
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

void makeOutputFiles(SymbolList* data_symbols, SymbolList* entry_symbols,
	SymbolList* extern_symbols, MemoryArray* data_array, MemoryArray* instruction_array)
{
	FILE* file = fopen("C:\\Users\\okopn\\Desktop\\university\\clab\\output.txt", "w");
	if (file == NULL) {
		printf("Error opening file");
		exit(1);
	}
	makeObjectFile(file, data_array, instruction_array);

	FILE* file2 = fopen("C:\\Users\\okopn\\Desktop\\university\\clab\\outputentries.txt", "w");

	if(entry_symbols!=NULL)
		makeEntriesFile(file2, entry_symbols, data_symbols);


	// Close the file
	


}