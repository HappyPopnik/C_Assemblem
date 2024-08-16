typedef struct Error {
    int error_code;
    char* error_message;
} Error;

typedef enum ERROR_CODES {
    MACRO_ALREADY_EXISTS,
    ILLEGAL_MACRO_NAME,
    SYMBOL_ALREADY_EXISTS,
    EXCEEDED_MEMORY_LIMIT,
    NO_SPACE_SEPARATION,
    LABEL_LENGTH_EXCEEDED,
    LABEL_NOT_FOUND,
    MISSING_QUOTES,
    INVALID_OPERATION,
    INVALID_REGISTER,
    NUMBER_CONVERSION_ERROR,
    ILLEGAL_DELIVERING,
    INSUFFICIENT_ARGUMENTS,
    TOO_MANY_ARGS,
    TWO_ARGUMENTS_INSTEAD_OF_ONE,
    LABEL_NOT_SYMBOLS,
    FILE_NOT_OPEN

}ERROR_CODES;

void print_error(int error_code, int line, char* file_name);
void print_external_error(int error_code, char* file_name, char* additional);