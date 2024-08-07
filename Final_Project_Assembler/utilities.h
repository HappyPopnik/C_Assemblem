#pragma once

#define MAX_LINE_LENGTH 81

#define MAX_MEMORY_SIZE 4096

#define MAX_LABEL_LENGTH 31

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
int isComment(char* line);
void remove_all_spaces(char* str);
void parse_numbers(const char* input, int* numbers, int* count);
char* trimAllWhitespace(char* str);