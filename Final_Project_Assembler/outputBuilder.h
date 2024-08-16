#include "memory_structs.h"

#define OCTAL_WORD_LENGTH 6 /* 5 chars and null terminator*/

void makeOutputFiles(SymbolList* data_symbols, SymbolList* entry_symbols,
	SymbolList* extern_symbols, MemoryArray* data_array, MemoryArray* instruction_array, char* filename);