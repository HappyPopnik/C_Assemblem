
/* macro struct - linked list made from name, it's content and the next node */
typedef struct macro {
    char* name;
    char* text;
    struct macro* next;
} macro;

/* Macro specifications */
#define MAX_MACRO_NAME_LEN 50
#define MAX_MACRO_TEXT_LEN 1000

/* global variable for the preprocessor to label that there are errors in macros */
extern int errors_found;

void macroExists(macro* head, const char* name, int line_num);
/* @ Function: macroExists(macro* head, const char* name, int line_num)
   @ Arguments:
       - head: Pointer to the head of the macro linked list.
       - name: Name of the macro to search for.
       - line_num: The current line number being processed in the source file.
   @ Description:
       Checks if a macro with the given name already exists in the linked list.
       If it does, it prints an error message and sets the `errors_found` flag to 1.
*/

void isRestrictedName(const char* name, int line_num);
/* @ Function: isRestrictedName(const char* name, int line_num)
   @ Arguments:
       - name: Name of the macro to check for restricted names.
       - line_num: The current line number being processed in the source file.
   @ Description:
       Checks if the macro name is a restricted name. If the name is restricted,
       it prints an error and sets the `errors_found` flag to 1.
*/

void AddMacroToList(macro** head, const char* name, const char* text);
/* @ Function: AddMacroToList(macro** head, const char* name, const char* text)
   @ Arguments:
       - head: Pointer to the head of the macro linked list.
       - name: Name of the macro to be added.
       - text: The text content of the macro.
   @ Description:
       Adds a new macro with the given name and text to the end of the macro linked list.
*/

void removeTrailingNewline(char* str);
/* @ Function: removeTrailingNewline(char* str)
   @ Arguments:
       - str: Pointer to a string where the trailing newline character will be removed.
   @ Description:
       Removes the trailing newline character from the given string if it exists.
*/

macro* findMacro(macro* head, const char* name);
/* @ Function: findMacro(macro* head, const char* name)
   @ Arguments:
       - head: Pointer to the head of the macro linked list.
       - name: The name of the macro to search for.
   @ Returns:
       Returns a pointer to the macro with the matching name, or NULL if not found.
   @ Description:
       Searches the macro linked list for a macro with the given name.
*/

macro* createMacroList(FILE* sourcefp);
/* @ Function: createMacroList(FILE* sourcefp)
   @ Arguments:
       - sourcefp: File pointer to the source file being processed.
   @ Returns:
       Returns a pointer to the head of the linked list of macros found in the source file.
   @ Description:
       Reads through the source file to find and store macros in a linked list.
*/

void integrateMacros(FILE* sourcefp, FILE* destfp, macro* head);
/* @ Function: integrateMacros(FILE* sourcefp, FILE* destfp, macro* head)
   @ Arguments:
       - sourcefp: File pointer to the source file being processed.
       - destfp: File pointer to the destination file where the output is written.
       - head: Pointer to the head of the macro linked list.
   @ Description:
       Reads the source file and replaces macros with their corresponding
       macro definitions, writing the result to the destination file.
*/

int preprocessFile(FILE* sourcefp, FILE* destfp, char* filename);
/* @ Function: preprocessFile(FILE* sourcefp, char* filename)
   @ Arguments:
       - sourcefp: File pointer to the source file being processed.
       - filename: Name of the file to write the preprocessed output to.
   @ Returns:
       Returns 1 if preprocessing is successful, 0 if errors are found.
   @ Description:
       Main logic of preprocessing. Enables the macro node creation and integration above.
*/