#include "memory_structs.h"

/* 5 chars and null terminator*/
#define OCTAL_WORD_LENGTH 6 


void makeObjectFile(FILE* file, MemoryArray* data_array, MemoryArray* instruction_array);
/*
   @ Function: makeObjectFile(FILE* file, MemoryArray* data_array, MemoryArray* instruction_array)
   @ Arguments:
       - file: A pointer to the file where the object data will be written.
       - data_array: A pointer to the data array.
       - instruction_array: A pointer to the instruction array.
   @ Description:
        Writes the object file output with the sizes of instruction and data arrays.
        Formats each entry in the instruction and data arrays as octal strings and writes them to the file.
*/

void makeEntriesFile(FILE* file, SymbolList* entry_symbols);
/*
@ Function: makeEntriesFile(FILE* file, SymbolList* entry_symbols)
   @ Arguments:
       - file: A pointer to the file where the entries data will be written.
       - entry_symbols: A pointer to the entry SymbolList.
   @ Description:
        Writes the entries file output with labels and their memory locations.
        Iterates through the list of entry symbols and writes each symbol's label and memory location to the file.
*/

void makeExternsFile(FILE* file, SymbolList* extern_symbols);
/*
@ Function: makeExternsFile(FILE* file, SymbolList* extern_symbols)
   @ Arguments:
       - file: A pointer to the file where the externs data will be written.
       - extern_symbols: A pointer to the external SymbolList.
   @ Description:
        Writes the externs file output with labels and their line numbers.
        Iterates through the list of extern symbols and writes each symbol's label and line numbers to the file.
*/


void makeOutputFiles(SymbolList* data_symbols, SymbolList* entry_symbols,
	SymbolList* extern_symbols, MemoryArray* data_array, MemoryArray* instruction_array, char* filename);
/*
@ Function: makeOutputFiles
   @ Arguments:
       All Symbol lists and memory arrays from second pass.
   @ Description:
        Creates the output files for the object, entries, and externs,
        Using the functions above.
*/