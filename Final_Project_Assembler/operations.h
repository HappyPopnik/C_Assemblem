#define NUM_OF_OPERATIONS 16

typedef struct operation {
    const char* operation_name;    
    int arguments;     /* How many arguments the opperation takes */
} operation;

static operation operations[] = {
        {"INVALID", 0},
        {"mov",  2},
        {"cmp",  2},
        {"add",  2},
        {"sub",  2},
        {"lea",  2},
        {"clr",  1},
        {"not",  1},
        {"inc",  1},
        {"dec",  1},
        {"jmp",  1},
        {"bne",  1},
        {"red",  1},
        {"prn",  1},
        {"jsr",  1},
        {"rts",  0},
        {"stop", 0}
};