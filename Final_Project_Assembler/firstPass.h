#include "memory_structs.h"

void symbolExists(SymbolList* head, const char* name, int line_num);
/* @ Function: symbolExists(SymbolList* head, const char* name, int line_num)
   @ Arguments:
       - head: Pointer to the head of symbol list.
       - name: Name of the symbol to check for.
       - line_num: The current line number being processed.
   @ Description:
       Checks if a symbol with the given name already exists in the symbol list.
       If it does, prints an error message indicating that the symbol already exists.
*/

void addSymbolToTable(SymbolList** head, char* label, int dc, int data_type);
/* @ Function: addSymbolToTable(SymbolList** head, char* label, int dc, int data_type)
   @ Arguments:
       - head: Pointer to the pointer of the head of the symbol list.
       - label: Name of the symbol to add.
       - dc: Data counter to append to the symbol.
       - data_type: Type of the symbol.
   @ Description:
       Adds a new symbol with the given label, data counter, and type to the symbol list.
*/

void checkMemorySize(int ic, int dc, int line_num);
/* @ Function: checkMemorySize(int ic, int dc, int line_num)
   @ Arguments:
       - ic: Instruction counter.
       - dc: Data counter.
       - line_num: The current line number being processed.
   @ Description:
       Checks if the combined instruction and data memory size exceeds the maximum allowed size.
       If it does, prints an error message indicating that the memory limit has been exceeded.
*/

void jumpSpaceSepatation(char** line_pos, int line_number);
/* @ Function: jumpSpaceSeparation(char** line_pos, int line_number)
   @ Arguments:
       - line_pos: Pointer to the position in the line to check for space separation.
       - line_number: The current line number being processed.
   @ Description:
       Checks for space separation at the given position in the line.
       If space is missing, prints an error message.
*/

void increaseDataSymbolsByIC(SymbolList* symbols, int ic);
/* @ Function: increaseDataSymbolsByIC(SymbolList *symbols, int ic)
   @ Arguments:
       - symbols: Pointer to the head of the symbol list.
       - ic: Instruction counter.
   @ Description:
       Increases the data counter (dc) for all data symbols by the instruction counter.
*/

void startFirstPass(FILE* sourcefp, char* filename);
/* @ Function: startFirstPass(FILE* sourcefp, char *filename)
   @ Arguments:
       - sourcefp: File pointer to the source file being processed.
       - filename: Name of the file to write the results int the end.
   @ Description:
       Processes the source file in the first pass to build the symbol table and memory arrays.
       It identifies labels, handles different types of data,
       and updates the symbol table and memory arrays.
       After completing the first pass, it starts the second pass.
*/
