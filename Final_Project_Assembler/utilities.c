#include "utilities.h"
#include <stdio.h>

char* trimWhiteSpaceFromStart(char* str)
{
	while (isspace((unsigned char)*str)) str++;
	return str;
}

int isComment(char* line) 
{
	return line[0] == ';';
}

int isNewLine(char* line)
{
    return line[0] == '\n';
}

int containsCommaOrSpace(char* pos)
{
    char* str = pos;
    while (*str) {
        if (*str == ',') {
            return 1;
        }
        if (isspace((unsigned char)*str)) {
            return 1; 
        }
        str++;
    }
    return 0;
}

void remove_all_spaces(char* str) {
    char* src = str;
    char* dst = str;
    int in_number = 0;

    while (*src) {
        if (isdigit(*src) || (*src == '-' && (src == str || !isdigit(*(src - 1))))) {
            // Handle negative sign if it's at the beginning or after a comma
            if (*src == '-') {
                *dst++ = *src++;
                continue;
            }
            in_number = 1;
            *dst++ = *src++;
        }
        else if (*src == ',' || isspace(*src)) {
            if (in_number) {
                *dst++ = *src;
                if (*src == ',') {
                    in_number = 0; // End of number
                }
            }
            src++;
        }
        else {
            *dst++ = *src++;
        }
    }
    *dst = '\0'; // Null-terminate the modified string
}

void parse_numbers(const char* input, int* numbers, int* count) {
    // Make a copy of the input string to work with
    *numbers = NULL;
    char* str = strdup(input);
    char* token;
    *count = 0;

    // Remove all spaces except those between numbers
    remove_all_spaces(str);

    // Check if the string is empty after processing
    if (strlen(str) == 0) {
        printf("Error: Input string is empty or invalid.\n");
        free(str);
        exit(0);
    }

    // Check for consecutive commas without numbers
    for (size_t i = 0; i < strlen(str) - 1; i++) {
        if (str[i] == ',' && str[i + 1] == ',') {
            printf("Error: Input string contains consecutive commas without a number between them.\n");
            free(str);
            exit(0);
        }
    }

    // Tokenize the string by commas
    token = strtok(str, ",");
    while (token != NULL) {
        // Trim leading and trailing whitespace from each token
        token = trimAllWhitespace(token);

        // Check for empty token (e.g., ",,")
        if (strlen(token) == 0) {
            printf("Error: Input string contains consecutive commas without a number between them.\n");
            free(str);
            exit(0);
        }

        numbers[(*count)++] = atoi(token);
        token = strtok(NULL, ",");
    }

    // Free the allocated copy of the string
    free(str);
}

char* trimAllWhitespace(char* str) {
    char* start, * end;

    // Trim leading space
    start = str;
    while (*start == ' ') {
        start++;
    }

    // If the string is all spaces
    if (*start == '\0') {
        return start;
    }

    // Trim trailing space
    end = start + strlen(start) - 1;
    while (end > start && *end == ' ') {
        end--;
    }

    // Write new null terminator
    *(end + 1) = '\0';

    return start;
}

void removeNewLine(char* str) {
    char* end = str + strlen(str) - 1;

    // Check if the last character is '\n' and replace it with '\0'
    if (end >= str && *end == '\n') {
        *end = '\0';
    }
}
char* to_15bit_binary(int n) {
    static char binary_str[16]; // 15 bits + null terminator
    int i;

    if (n < 0 || n > 32767) { // 15-bit maximum value
        return NULL; // Out of range
    }

    for (i = 0; i < 15; i++) {
        binary_str[i] = (n & (1 << (14 - i))) ? '1' : '0';
    }

    binary_str[15] = '\0'; // Null terminator
    return binary_str;
}