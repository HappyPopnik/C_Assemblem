#include <stdlib.h>
#include "memory_structs.h"


void addWord(MemoryArray *Mem_array, Word newWord) {
    // Reallocate memory for the array to add one more element
    Mem_array->marray = realloc(Mem_array->marray, (Mem_array->size + 1) * sizeof(Word));
    if (Mem_array->marray == NULL) {
        perror("Failed to reallocate memory");
        exit(EXIT_FAILURE);
    }
    Mem_array->marray[Mem_array->size] = newWord;
    Mem_array->size++;

}

MemoryArray* createMemoryArray() {
    MemoryArray* NewMemoryArray = (MemoryArray*)malloc(sizeof(MemoryArray));
    if (NewMemoryArray == NULL) {
        perror("Failed to allocate memory for WordArray");
        exit(EXIT_FAILURE);
    }
    NewMemoryArray->marray = NULL;
    NewMemoryArray->size = 0;
    return NewMemoryArray;
}