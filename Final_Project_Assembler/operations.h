#include "utilities.h"
#include "memory_structs.h"

#define NUM_OF_OPERATIONS 16

#define NUM_OF_REGISTERS 8

#define IMMIDIATE_ADDRESSING 0

#define DIRECT_ADDRESSING 1

#define INDIRECT_REG_ADDRESSING 2

#define DIRECT_REG_ADDRESSING 3

#define A_FLAG 4

#define R_FLAG 2

#define E_FLAG 1

#define SOURCE_DIRECTION 1

#define DESTINATION_DIRECTION 2



typedef struct operation {
    const char* operation_name;    
    int arguments;     /* How many arguments the opperation takes */
    int op_code;
    int possible_src_delivery_opts[4];
    int possible_dest_delivery_opts[4];
} operation;

typedef struct registry {
    const char* registry_name;
    int registry_code;
} registry;

static operation operations[] = {
        {"INVALID", 0, 0,  {NULL},     NULL},
        {"mov",     2, 0,  {0,1,2,3},  {1,2,3}},
        {"cmp",     2, 1,  {0,1,2,3},  {0,1,2,3}},
        {"add",     2, 2,  {0,1,2,3},  {1,2,3}},
        {"sub",     2, 3,  {0,1,2,3},  {1,2,3}},
        {"lea",     2, 4,  {1},        {1,2,3}},
        {"clr",     1, 5,  {NULL},     {1,2,3}},
        {"not",     1, 6,  {NULL},     {1,2,3}},
        {"inc",     1, 7,  {NULL},     {1,2,3}},
        {"dec",     1, 8,  {NULL},     {1,2,3}},
        {"jmp",     1, 9,  {NULL},     {1,2}},
        {"bne",     1, 10, {NULL},     {1,2}},
        {"red",     1, 11, {NULL},     {1,2,3}},
        {"prn",     1, 12, {NULL},     {0,1,2,3}},
        {"jsr",     1, 13, {NULL},     {1,2}},
        {"rts",     0, 14, {NULL},     NULL},
        {"stop",    0, 15, {NULL},     NULL}
};

static registry registries[] = {
    {"r0", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4},
    {"r5", 5},
    {"r6", 6},
    {"r7", 7}
};


Word* MakeWord(char* pos, int operation_index, int* size);