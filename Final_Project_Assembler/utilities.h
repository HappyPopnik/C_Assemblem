#pragma once

#define MAX_LINE_LENGTH 81

#define MAX_MEMORY_SIZE 4096

#define MAX_LABEL_LENGTH 31

#define BIN_TO_INT(b) ( \
    ((b & 0b1) << 0) | \
    ((b & 0b10) >> 1) | \
    ((b & 0b100) >> 2) | \
    ((b & 0b1000) >> 3) | \
    ((b & 0b10000) >> 4) | \
    ((b & 0b100000) >> 5) | \
    ((b & 0b1000000) >> 6) | \
    ((b & 0b10000000) >> 7) | \
    ((b & 0b100000000) >> 8) | \
    ((b & 0b1000000000) >> 9) | \
    ((b & 0b10000000000) >> 10) | \
    ((b & 0b100000000000) >> 11) | \
    ((b & 0b1000000000000) >> 12) | \
    ((b & 0b10000000000000) >> 13) | \
    ((b & 0b100000000000000) >> 14) \
)

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
int isNewLine(char* line);
void removeNewLine(char* str);
char* to_15bit_binary(int n);