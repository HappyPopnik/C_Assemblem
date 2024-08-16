#include "errors.h"
#include <stdio.h>

Error errors[] = {
	{ MACRO_ALREADY_EXISTS, "Macro already exists" },
	{ ILLEGAL_MACRO_NAME, "Illeagl macro name, this is a saved word"},
	{ TWO_ARGUMENTS_INSTEAD_OF_ONE, "Expected one argument, but received 2"}
};

void print_error(int error_code, int line, char* file_name)
{
	printf("Error in file: %s, line: %d: %s\n", file_name, line, errors[error_code].error_message);
}