#pragma once

/* Global variable to the current processed file the assembler handles */
extern char* current_processed_file;

/* Meta defining types of the project */
#define MAX_FILE_NAME_LENGTH 256
#define MAX_LINE_LENGTH 81
#define MAX_MEMORY_SIZE 4096
#define MAX_LABEL_LENGTH 31

/* All saved names which label or symbol is not allowed to be named as */
static char* saved_names[] = {
	"mov",
	"cmp",
	"add",
	"sub",
	"lea",
	"clr",
	"not",
	"inc",
	"dec",
	"jmp",
	"bne",
	"red",
	"prn",
	"jsr",
	"rts",
	"stop",
	"macr",
	"endmacr",
	".data",
	".string",
	".entry",
	".extern",
	"r0",
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"r7"
};

char* trimWhiteSpaceFromStart(char* str);
/* @ Function: trimWhiteSpaceFromStart(char* str)
   @ Arguments: The function takes a pointer to a string (char* str).
   @ Description: This function removes whitespace from the input string.
   It iterates through the string until it finds the first non-whitespace character.
*/

int isComment(char* line);
/* @ Function: isComment(char* line)
   @ Arguments: The function takes a pointer to a string (char* line).
   @ Description: This function checks if the given line starts with a ';'.
*/

void removeAllSpaces(char* str);
/* @ Function: removeAllSpaces(char* str)
   @ Arguments: The function takes a pointer to a string (char* str).
   @ Description: This function removes all spaces from the input string. It iterates through the string.
*/

int containsCommaOrSpace(char* pos);
/* @ Function: containsCommaOrSpace(char* pos)
   @ Arguments: The function takes a pointer to a string (char* pos).
   @ Description: This function iterates the input string to determine if it contains ','
   or ' '.
*/

void parseNumbers(const char* input, int* numbers, int* count, int line);
/* @ Function: parseNumbers(const char* input, int* numbers, int* count, int line)
   @ Arguments: The function takes a string (const char* input), an array of integers (int* numbers),
				a pointer to an integer (int* count), and an integer representing the line number (int line).
   @ Description: This function parses a comma separated string of numbers. It first removes all spaces
   from the input string and then splits the string into tokens based on commas. Each token is
   converted to integer and stored in the numbers array.
*/

char* trimAllWhitespace(char* str);
/* @ Function: trimAllWhitespace(char* str)
   @ Arguments: The function takes a pointer to a string (char* str).
   @ Description: This function removes all leading and trailing whitespace from the input string.
*/

int isNewLine(char* line);
/* @ Function: isNewLine(char* line)
   @ Arguments: The function takes a pointer to a string (char* line).
   @ Description: This function checks if the given line is a newline character ('\n').
*/

void removeNewLine(char* str);
/* @ Function: removeNewLine(char* str)
   @ Arguments: The function takes a pointer to a string (char* str).
   @ Description: This function checks if the last character of the input string is a newline character ('\n').
   If it is, the function replaces it with a null terminator.
*/

void intToOctalString(int num, char* str);
/* @ Function: intToOctalString(int num, char* str)
   @ Arguments: The function takes an integer (int num) and a pointer to a string (char* str).
   @ Description: This function converts the given integer to its octal representation and
   formats it as a string that is 5 characters wide.
*/

void trimTrailingSpaces(char* str);
/* @ Function: trimTrailingSpaces(char* str)
   @ Arguments: The function takes a pointer to a string (char* str).
   @ Description: This function removes any trailing spaces from the input string.
*/