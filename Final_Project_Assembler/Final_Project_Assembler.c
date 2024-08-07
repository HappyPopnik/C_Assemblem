#include <stdio.h>
#include "preprocessor.h"
#include "firstPass.h"
#pragma warning(disable : 4996)

int main()
{
    FILE* file = fopen("C:\\Users\\okopn\\Desktop\\university\\clab\\test.txt", "r");
    FILE* file2 = fopen("C:\\Users\\okopn\\Desktop\\university\\clab\\test2.txt", "w");

    if (!file) {
        perror("Failed to open file");
        return;
    }
    preprocessFile(file, file2);
    fclose(file2);
    FILE* file3 = fopen("C:\\Users\\okopn\\Desktop\\university\\clab\\test2.txt", "r");
    startFirstPass(file3);
    return 0;
}