#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../sudoku.h"

int main(int argc, char *argv[])
{
    FILE *file;
    char ch;
    file = fopen("sudoku.txt", "r");
    do
    {
        ch = fgetc(file);
        putchar(ch);
    } while (ch != EOF);
    fclose(file);
    char *verticalSeparator = "|";
    char *horizontalSeparator = "=";
    char const *nameOfFile = "sudoku.txt";
    uint8_t buffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (uint8_t i = 1; i <= 9; i++)
    {
        if (checkFile(nameOfFile))
        {
            exit(1);
        }
        getSquareFROMFILE(nameOfFile, verticalSeparator, horizontalSeparator, i, buffer);
        printBuffer(buffer);
    }
    return 0;
}
