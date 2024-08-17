#include "memory_structs.h"

void iterateThroughMemArray(MemoryArray* wordArray, SymbolList* data_symbols, SymbolList* external_symbols);
/* @ Function: iterateThroughMemArray(MemoryArray* wordArray, SymbolList* data_symbols, SymbolList* external_symbols)
   @ Arguments: Takes a pointer to a MemoryArray (MemoryArray* wordArray), a pointer to a list of data symbols
				(SymbolList* data_symbols), and a pointer to a list of external symbols (SymbolList* external_symbols).
   @ Description: Iterates through each word in the memory array. If the word represents a label,
   the function searches for the label in the data symbols list. If found, the label's address and the 'R' flag
   are encoded into the word. If not found in data symbols, it searches the external symbols list and encodes the word with
   the 'E' (external) flag if the label is found.
*/

void formatEntries(SymbolList* entry_symbols, SymbolList* data_symbols);
/* @ Function: formatEntries(SymbolList* entry_symbols, SymbolList* data_symbols)
   @ Arguments: Takes a pointer to a Symbol list of entry symbols (SymbolList* entry_symbols) and a pointer
				to a Symbol list of data symbols (SymbolList* data_symbols).
   @ Description: For each entry symbol in the entry_symbols list, the function searches for the right
   symbol in the data_symbols list. If a match is found, it assigns the address (dc) of the data symbol to the entry symbol.
*/

void formatExterns(SymbolList* extern_symbols, MemoryArray* instruction_array);
/* @ Function: formatExterns(SymbolList* extern_symbols, MemoryArray *instruction_array)
   @ Arguments: Takes a pointer to a list of external symbols (SymbolList* extern_symbols) and a pointer
				to a memory array containing instructions (MemoryArray* instruction_array).
   @ Description: This function iterates over the instruction array and for each external symbol it searches for the right
   symbol in the extern_symbols list.
   If found, it records the location of the instruction word in the extern_placements array of the external symbol
   and increments the externs_count.
*/

void startSecondPass(SymbolList *data_symbols, SymbolList *entry_symbols, 
	SymbolList *extern_symbols, MemoryArray *data_array, MemoryArray *instruction_array, char* filename);
/* @ Function: startSecondPass(SymbolList *data_symbols, SymbolList *entry_symbols, 
	SymbolList *extern_symbols, MemoryArray *data_array, MemoryArray *instruction_array, char* filename)
   @ Arguments: All Symbol lists and memory arrays from first pass
   @ Description: This function creates the logic behind the second pass, activating the above functions.
   And continuing to the building of the files.
*/

