typedef struct {
    unsigned int bits : 15;
    char* symb_name;
} Word;

typedef struct {
    Word* marray;
    size_t size;
} MemoryArray;

void addWord(MemoryArray* Mem_array, Word newWord);
MemoryArray* createMemoryArray();

