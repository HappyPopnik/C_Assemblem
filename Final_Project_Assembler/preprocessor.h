
typedef struct macro {
    char* name;
    char* text;
    struct macro* next;
} macro;

#define MAX_MACRO_NAME_LEN 50
#define MAX_MACRO_TEXT_LEN 1000

int preprocessFile(FILE* sourcefp, FILE* destfp, char* filename);
//char* trimWhiteSpaceFromStart(char* str);
//void AddMacroToList(macro** head, const char* name, const char* text);