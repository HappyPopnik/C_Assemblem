#include "utilities.h"
#include <stdio.h>
#include "errors.h"

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

void removeAllSpaces(char* str) {
    char* src = str;
    char* dst = str;
    int in_number = 0;

    while (*src) {
        if (isdigit(*src) || (*src == '-' && (src == str || !isdigit(*(src - 1))))) {
            /* allow negative sign at start of number*/
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
                    in_number = 0;
                }
            }
            src++;
        }
        else {
            *dst++ = *src++;
        }
    }
    *dst = '\0'; /* Null - terminate the modified string */
}

void parseNumbers(const char* input, int* numbers, int* count, int line) {
    *numbers = NULL;
    char* str = strdup(input);
    char* token;
    *count = 0;

    removeAllSpaces(str);

    token = strtok(str, ",");
    while (token != NULL) {
        /* Remove whitespace */
        token = trimAllWhitespace(token);

        /* Check for ,, situation */
        if (strlen(token) == 0) {
            printError(TWO_COMMAS, line, current_processed_file);
        }

        numbers[(*count)++] = atoi(token);
        token = strtok(NULL, ",");
    }
}

char* trimAllWhitespace(char* str) {
    char* start, * end;

    start = str;
    while (*start == ' ') {
        start++;
    }

    /* If the staring is spaces only */
    if (*start == '\0') {
        return start;
    }

    end = start + strlen(start) - 1;
    while (end > start && *end == ' ') {
        end--;
    }

    /* New null terminator */
    *(end + 1) = '\0';

    return start;
}

void removeNewLine(char* str) {
    char* end = str + strlen(str) - 1;

    /* Check if the last character is '\n' and replace it with '\0' */
    if (end >= str && *end == '\n') {
        *end = '\0';
    }
}

void intToOctalString(int num, char* str) {
    /* Format as 5 characters wide, padded with zeros */
    snprintf(str, 6, "%05o", num);
}

void trimTrailingSpaces(char* str) {
    if (str == NULL) return; 
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        len--;
    }
    str[len] = '\0';
}