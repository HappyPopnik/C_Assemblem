#include <stdlib.h>
#include "memory_structs.h"


void addWord(MemoryArray *Mem_array, Word newWord) {
    /* Reallocate memory for the array to add one more element */
    Mem_array->marray = realloc(Mem_array->marray, (Mem_array->size + 1) * sizeof(Word));
    Mem_array->marray[Mem_array->size] = newWord;
    Mem_array->size++;

}

MemoryArray* createMemoryArray() {
    MemoryArray* NewMemoryArray = (MemoryArray*)malloc(sizeof(MemoryArray));
    NewMemoryArray->marray = NULL;
    NewMemoryArray->size = 0;
    return NewMemoryArray;
}