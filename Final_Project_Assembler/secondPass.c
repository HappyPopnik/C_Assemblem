#include <stdio.h>
#include "secondPass.h"
#include "operations.h"
#include "outputBuilder.h"

void iterateThroughMemArray(MemoryArray* wordArray, SymbolList* data_symbols, SymbolList* external_symbols) {
	for (int i = 0; i < wordArray->size; ++i)
	{
		if (wordArray->marray[i].bits == 0) /* It is a label */
		{
			/* Search the label name through symbol list. */
			int found_symbol = 0;
			char* label_name = wordArray->marray[i].symb_name;
			SymbolList* symbols_pos = data_symbols;
			while (symbols_pos != NULL) {
				if (strcmp(symbols_pos->label, label_name) == 0)
				{
					/* Found the label is data symbols list */
					/* Add R flag */
					int word_encoding = 0;
					word_encoding = word_encoding + R_FLAG;
					word_encoding = word_encoding + (symbols_pos->dc << 3);
					wordArray->marray[i].bits = word_encoding;
					printf("test");
					found_symbol = 1;
					break;
				}
				symbols_pos = symbols_pos->next;
			}
			if (!found_symbol)
			/* If not found symbol in data symbols, look at external symbols */
			{
				SymbolList* symbols_pos = external_symbols;
				while ((symbols_pos != NULL)) {
					if (strcmp(symbols_pos->label, label_name) == 0)
					{
						/* Found the label is data symbols list */
						/* Add E flag */
						int word_encoding = 0;
						word_encoding = word_encoding + E_FLAG;
						wordArray->marray[i].bits = word_encoding;
						found_symbol = 1;
						break;
					}
					symbols_pos = symbols_pos->next;
				}
				if (!found_symbol)
				/* if not found in external, its not anywhere. Illegal label detected. */
				{
					printf("label %s not found in symbol table.", label_name);
					exit(1);
				}
			}
		}
	}
}

void startSecondPass(SymbolList* data_symbols, SymbolList* entry_symbols,
	SymbolList* extern_symbols, MemoryArray* data_array, MemoryArray* instruction_array)
{
	iterateThroughMemArray(instruction_array, data_symbols, extern_symbols);

	makeOutputFiles(data_symbols, entry_symbols, extern_symbols, data_array, instruction_array);

	printf("*******************************************************\n");
	printLinkedList(data_symbols, 0);
	printf("**********************\n");
	printLinkedList(entry_symbols, 0);
	printf("**********************\n");
	printLinkedList(extern_symbols, 0);
	printf("**********************\nData array: \n");
	printWordArray(data_array, 0);
	printf("**********************\ninstruction array: \n");
	printWordArray(instruction_array, 2);
	printf("**********************\n");

}