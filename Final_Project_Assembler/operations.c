#include <stdio.h>
#include "operations.h"

int operationExistsInOParray(char* operation_name) {
    for (size_t i = 0; i < NUM_OF_OPERATIONS; i++) {
        if (strncmp(operation_name, operations[i].operation_name, sizeof(operations[i].operation_name) -1) == 0) {
            return i;
        }
    }
    return 0;
}