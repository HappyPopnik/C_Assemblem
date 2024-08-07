#include <stdio.h>
#include "preprocessor.h"
#include "utilities.h"

#pragma warning(disable : 4996)

void macroExists(macro* head, const char* name) {
	macro* current = head;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			printf("Error: Macro with name '%s' already exists.\n", name);
			exit(1);
		}
		current = current->next;
	}
}

void isRestrictedName(const char* name) {
	size_t restrictedArraySize = sizeof(saved_names) / sizeof(saved_names[0]);
	for (int i = 0; i < restrictedArraySize; i++) {
		if (strcmp(saved_names[i], name) == 0) {
			printf("Error: Macro with name '%s' is forbidden.\n", name);
			exit(1);
		}
	}
}

void AddMacroToList(macro **head, const char *name, const char *text)
{
	macro* newmacro = (macro*)malloc(sizeof(macro));
	newmacro->name = strdup(name);
	newmacro->text = strdup(text);
	newmacro->next = NULL;
	if (*head == NULL)
	{
		*head = newmacro;
	}
	else
	{
		macro *current = *head;
		while (current->next != NULL) 
		{
			current = current->next;
		}
		current->next = newmacro;
	}
}

void removeTrailingNewline(char* str) {
	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}
}

macro* findMacro(macro* head, const char* name) {
	macro* current = head;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

macro* createMacroList(FILE* sourcefp)//, FILE* destfp)
{
	int macr_exists_flag = 0;
	macro *head = NULL;
	char line[MAX_LINE_LENGTH];
	char macroName[MAX_MACRO_NAME_LEN];
	char *macroText = NULL;
	size_t macroTextSize = 0;

	while (fgets(line, sizeof(line), sourcefp))
	{
		char* trimmedLine = trimWhiteSpaceFromStart(line);
		printf(trimmedLine);
		if (macr_exists_flag)
		{
			if (strncmp(trimmedLine, "endmacr", 7) == 0) 
			{
				if (macroTextSize > 0 && macroText[macroTextSize - 1] == '\n') {
					macroText[macroTextSize - 1] = '\0';
				}
				AddMacroToList(&head, macroName, macroText);
				macr_exists_flag = 0;
			}
			else
			{
				size_t len = strlen(trimmedLine);
				macroText = (char*)realloc(macroText, macroTextSize + len + 1); // +2 for newline and null terminator
				memcpy(macroText + macroTextSize, trimmedLine, len);
				macroText[macroTextSize + len] = '\0'; // Null terminate
				macroTextSize += len; //+ 1; // Update textSize to include the newline character
			}
		}
		else
		{
			if (strncmp(trimmedLine, "macr", 4) == 0) {
				// Start of a new macro definition
				sscanf(trimmedLine, "macr %255s", macroName);
				macroExists(head, macroName);
				isRestrictedName(macroName);
				macr_exists_flag = 1;
				macroText = (char*)malloc(1);
				macroText[0] = '\0';
				macroTextSize = 0;
			}
		}
	}
	return head;
}

void integrateMacros(FILE* sourcefp, FILE* destfp, macro* head)
{
	int in_macr = 0;
	char line[MAX_LINE_LENGTH];
	printf("\n************\n");

	while (fgets(line, sizeof(line), sourcefp)) {
		char* trimmedLine = trimWhiteSpaceFromStart(line);
		removeTrailingNewline(trimmedLine);
		if (strncmp(trimmedLine, "macr", 4) == 0)
		{
			in_macr = 1;
			continue;
		}
		else if (strncmp(trimmedLine, "endmacr", 7) == 0)
		{
			in_macr = 0;
			continue;
		}
		else if (in_macr)
		{
			continue;
		}
		macro* macro = findMacro(head, trimmedLine);
		if (macro) {
			fputs(macro->text, destfp);
			fputs("\n", destfp);
		}
		else {
			fputs(line, destfp);
			fputs("\n", destfp);
		}
	}
}

void preprocessFile(FILE* sourcefp, FILE* destfp)
{
	macro* head = createMacroList(sourcefp);
	fseek(sourcefp, 0, SEEK_SET);
	integrateMacros(sourcefp, destfp, head);
}