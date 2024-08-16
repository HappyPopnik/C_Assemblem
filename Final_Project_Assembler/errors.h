typedef struct Error {
    int error_code;
    char* error_message;
} Error;

typedef enum ERROR_CODES {
    MACRO_ALREADY_EXISTS,
    ILLEGAL_MACRO_NAME,
    SYMBOL_ALREADY_EXISTS,
    TWO_ARGUMENTS_INSTEAD_OF_ONE

}ERROR_CODES;

void print_error(int error_code, int line, char* file_name);