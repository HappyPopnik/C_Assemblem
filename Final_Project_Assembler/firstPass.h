#define DATA 1

#define STRING 2

#define EXTERNAL 3

#define ENTRY 4

#define CODE 5

typedef struct SymbolList {
    char* label;
    int data_type;
    int dc;
    struct SymbolList* next;
} SymbolList;

void startFirstPass(FILE* sourcefp);