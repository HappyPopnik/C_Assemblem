#include <stdio.h>
#include "secondPass.h"
#include "operations.h"
#include "outputBuilder.h"
#include "errors.h"

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
					print_external_error(LABEL_NOT_SYMBOLS, current_processed_file, label_name);
				}
			}
		}
	}
}

void formatEntries(SymbolList* entry_symbols, SymbolList* data_symbols)
{
	SymbolList* entry_current = entry_symbols;
	while (entry_current != NULL)
	{
		char* label = entry_current->label;
		SymbolList* data_current = data_symbols;
		while (data_current != NULL)
		{
			if (strcmp(data_current->label, label) == 0)
			{
				entry_current->dc = data_current->dc;
			}
			data_current = data_current->next;
		}
		entry_current = entry_current->next;
	}
}

void formatExterns(SymbolList* extern_symbols, MemoryArray *instruction_array)
{
	SymbolList* externs_current = extern_symbols;
	for (int i = 0; i < instruction_array->size; i++)
	{
		if (instruction_array->marray[i].bits == 1)
		{
			while (externs_current != NULL)
			{
				if (strcmp(instruction_array->marray[i].symb_name, externs_current->label) == 0)
				{				
					// Reallocate to add more space as externs_count increases
					externs_current->extern_placements = realloc(externs_current->extern_placements, sizeof(int) * (externs_current->externs_count + 1));
					externs_current->extern_placements[externs_current->externs_count] = i + 100;
					externs_current->externs_count = externs_current->externs_count + 1;
				}

				externs_current = externs_current->next;
			}
			externs_current = extern_symbols;
		}
		
	}
	/*
	Todo:
	1) iterate through instruction array
	2) for each instruction check if bits are set to 1
	3) if yes, get its name, and iterate through extern symbols
	3) add to the extern placements of the symbol the dc number.
	*/
}

void startSecondPass(SymbolList* data_symbols, SymbolList* entry_symbols,
	SymbolList* extern_symbols, MemoryArray* data_array, MemoryArray* instruction_array, char* filename)
{
	iterateThroughMemArray(instruction_array, data_symbols, extern_symbols);

	formatEntries(entry_symbols, data_symbols);

	formatExterns(extern_symbols, instruction_array);

	makeOutputFiles(data_symbols, entry_symbols, extern_symbols, data_array, instruction_array, filename);
}