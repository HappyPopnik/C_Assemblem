#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct {
    unsigned int bits : 15;
    char* symb_name;
} Word;

typedef struct {
    Word* marray;
    size_t size;
} MemoryArray;

typedef struct SymbolList {
    char* label;
    int data_type;
    int dc;
    int* extern_placements;
    int externs_count;
    struct SymbolList* next;
} SymbolList;

void addWord(MemoryArray* Mem_array, Word newWord);
MemoryArray* createMemoryArray();


#endif