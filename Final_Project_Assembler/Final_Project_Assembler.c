#include <stdio.h>
#include "preprocessor.h"
#include "firstPass.h"
#include "utilities.h"
#include "errors.h"
#pragma warning(disable : 4996)

char* current_processed_file = NULL;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_external_error(WRONG_COMMANDLINE, NULL, NULL);
        exit(1);
    }

    /* Iterate through the files */
    for (int i = 1; i < argc; i++) {

        current_processed_file = argv[i];

        char filename[MAX_FILE_NAME_LENGTH];

        filename[0] = '\0';
        strcpy(filename, argv[i]);
        /* format to .as extension */
        strcat(filename, ".as");

        FILE* assembly_file = fopen(filename, "r");

        if (assembly_file == NULL) {
            print_external_error(FILE_NOT_EXIST, current_processed_file, filename);
        }

        /* Open a post macro file, change file name by changing only extension */
        strcpy(strrchr(filename, '.') + 1, "am");
        
        if (preprocessFile(assembly_file, filename, argv[i]) == 0)
        {
            /* Macro listing failed because of errors */
            continue;
        }
        fclose(assembly_file);
        FILE *post_macro_file = fopen(filename, "r");
        if (post_macro_file == NULL) {
            print_external_error(FILE_NOT_OPEN, current_processed_file, filename);
            continue;
        }
        startFirstPass(post_macro_file, argv[i]);

        fclose(post_macro_file);
    }
}