#include <stdio.h>
#include "preprocessor.h"
#include "firstPass.h"
#include "utilities.h"
#pragma warning(disable : 4996)

char* current_processed_file = NULL;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename1> <filename2> ...\n", argv[0]);
        return 1;
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
            printf("File doesn't exist");
            continue;
        }

        /* Open a post macro file, change file name by changing only extension */
        strcpy(strrchr(filename, '.') + 1, "am");

        FILE* post_macro_file = fopen(filename, "w");

        if (post_macro_file == NULL) {
            perror(filename);
            continue;
        }

        if (preprocessFile(assembly_file, post_macro_file, argv[i]))
        {
            /* Macro listing failed because of errors */
            continue;
        }

        fclose(assembly_file);
        fclose(post_macro_file);
        
        post_macro_file = fopen(filename, "r");

        if (post_macro_file == NULL) {
            perror(filename);
            continue;
        }
       
        startFirstPass(post_macro_file, argv[i]);

        // Close the file
        fclose(post_macro_file);
    }
}