#include "errors.h"
#include <stdio.h>

Error errors[] = {
	{ MACRO_ALREADY_EXISTS, "Macro already exists" },
	{ ILLEGAL_MACRO_NAME, "Illeagl macro name, this is a saved word"},
	{ TWO_ARGUMENTS_INSTEAD_OF_ONE, "Expected one argument, but received 2"},
	{ EXCEEDED_MEMORY_LIMIT, "Exceeded memory limit"},
	{ NO_SPACE_SEPARATION, "Space separation between data call lacking"},
	{ LABEL_LENGTH_EXCEEDED, "Label length too long"},
	{ LABEL_NOT_FOUND, "label name not found"},
	{ MISSING_QUOTES, "No quotes found at end of string declaration"},
	{ TWO_COMMAS, "Two commas without number between them"},
	{ INVALID_OPERATION, "operation given is invalid"},
	{ INVALID_REGISTER, "Register numbner is not valid"},
	{ NUMBER_CONVERSION_ERROR, "Error in number conversion from int to char"},
	{ ILLEGAL_DELIVERING, "Illegal delivering option for this operation"},
	{ INSUFFICIENT_ARGUMENTS, "There are not enough arguements for this operation"},
	{ TOO_MANY_ARGS, "There are too many arguemnts in this line"},
	{ SYMBOL_ALREADY_EXISTS, "This symbol already exists in symbol table"},
	{ LABEL_NOT_SYMBOLS, "Label not found in symbol table: "},
	{ FILE_NOT_OPEN, "Cannot open the file: "},
	{ FILE_NOT_EXIST, "File does not exist: "}


};

void print_error(int error_code, int line, char* file_name)
{
	printf("Error in file: %s, line: %d: %s\n", file_name, line, errors[error_code].error_message);
}

void print_external_error(int error_code, char* file_name, char* additional)
{
	printf("Error in file: %s : %s %s\n", file_name, errors[error_code].error_message, additional);
}