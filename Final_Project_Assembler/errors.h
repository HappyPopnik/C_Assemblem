
/* Error structure */
typedef struct Error {
    int error_code; /* Error code, from the listed below */
    char* error_message; /* The given message it caries */
} Error;

/* Enum list of all error codes */
typedef enum ERROR_CODES {
    MACRO_ALREADY_EXISTS,
    ILLEGAL_MACRO_NAME,
    SYMBOL_ALREADY_EXISTS,
    EXCEEDED_MEMORY_LIMIT,
    NO_SPACE_SEPARATION,
    LABEL_LENGTH_EXCEEDED,
    LABEL_NOT_FOUND,
    MISSING_QUOTES,
    TWO_COMMAS,
    INVALID_OPERATION,
    INVALID_REGISTER,
    NUMBER_CONVERSION_ERROR,
    ILLEGAL_DELIVERING,
    INSUFFICIENT_ARGUMENTS,
    TOO_MANY_ARGS,
    TWO_ARGUMENTS_INSTEAD_OF_ONE,
    LABEL_NOT_SYMBOLS,
    FILE_NOT_OPEN,
    FILE_NOT_EXIST,
    WRONG_COMMANDLINE
}ERROR_CODES;

void printError(int error_code, int line, char* file_name);
/*
   @ Function: printError(int error_code, int line, char* file_name)
   @ Arguments:
       - error_code: The error code from the above list
       - line: The line the error code happened at.
       - file_name: The current file processed.
   @ Description:
        Prints the correct error responding to the error code.
*/

void print_external_error(int error_code, char* file_name, char* additional);
/*
   @ Function: print_external_error(int error_code, char* file_name, char* additional)
   @ Arguments:
       - error_code: The error code from the above list
       - additional: Additional information for the error representation.
       - file_name: The current file processed.
   @ Description:
        Prints the correct error responding to the error code with additinal information.
*/