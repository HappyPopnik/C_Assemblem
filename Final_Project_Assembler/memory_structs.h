

typedef struct {
    int bits : 15;
} Word;

typedef struct {
    Word* marray;
    size_t size;
} MemoryArray;

void addWord(MemoryArray* Mem_array, Word newWord);
MemoryArray* createMemoryArray();

