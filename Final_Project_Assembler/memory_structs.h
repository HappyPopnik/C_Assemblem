#ifndef HEADER_FILE
#define HEADER_FILE

/* Types of symbols */
#define DATA 1
#define STRING 2
#define EXTERNAL 3
#define ENTRY 4
#define CODE 5

/* The structure of a word in the memory. */
typedef struct {
    unsigned int bits : 15; /* A word is an int consisting of 15 bits */
    char* symb_name; /* In case the word is a label, the symb_name would have it's name as value */
} Word;

/* The memory array struct for the data and instructions array */
typedef struct {
    Word* marray; /* The words array */
    size_t size; /* Its size */
} MemoryArray;

/* The linked list struct of the symbols */
typedef struct SymbolList {
    char* label; /* Symbols label */
    int data_type; /* Symbols data type (listed above) */
    int dc; /* Symbols data count */
    int* extern_placements; /* For external symbols, the places it shows in the machine code */
    int externs_count; /* For external symbols, the number of times it appears  */
    struct SymbolList* next; /* The next symbol node */
} SymbolList;

void addWord(MemoryArray* Mem_array, Word newWord);
/*
   @ Function: addWord(MemoryArray* Mem_array, Word newWord)
   @ Arguments:
       - Mem_array: The memory array it add a word to.
       - newWord: The word added.
   @ Description:
        Add a new word to the memory array, and icreasing the memory array's size.
*/
MemoryArray* createMemoryArray();
/*
   @ Function: createMemoryArray()
   @ Description:
        Creates, allocates and returns an empty memory array.
*/

#endif