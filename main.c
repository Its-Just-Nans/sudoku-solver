#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sudoku.h"

int main(int argc, char *argv[])
{
    char *outputName = "sudokuValid.txt";
    char *verticalSeparator = "|";
    char *horizontalSeparator = "=";
    char *nameOfFile = "sudoku.txt";
    uint8_t memoryUse = 1;
    for (uint8_t count = 1; count < argc; count++)
    {
        if (argv[count][0] == '-')
        {
            if (argv[count][1] == 'o')
            {
                count++;
                outputName = argv[count];
            }
            else if (argv[count][1] == 'm')
            {
                count++;
                memoryUse = 0;
            }
            else if (argv[count][1] == 's')
            {
                if (argv[count][2] == 'v')
                {
                    count++;
                    verticalSeparator = argv[count];
                }
                else if (argv[count][2] == 'h')
                {
                    count++;
                    horizontalSeparator = argv[count];
                }
            }
        }
        else
        {
            nameOfFile = argv[count];
        }
    }
    uint16_t(*sudoku)[9][9][1];
    printf("-------Options-----\n");
    printf("outputName -> '%s'\n", outputName);
    printf("verticalSeparator -> '%s'\n", verticalSeparator);
    printf("horizontalSeparator -> '%s'\n", horizontalSeparator);
    printf("Entry file -> '%s'\n", nameOfFile);
    printf("Memory usage -> ");
    if (memoryUse)
    {
        printf("on\n");
        uint16_t sudokuVariable[9][9][1] = {{{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}};
        sudoku = &sudokuVariable;
        printf("Sudoku size : %d bytes or %d bits\n", (int)sizeof(*sudoku), (int)sizeof(*sudoku) * 8);
    }
    else
    {
        printf("limited\n");
    }
    printf("-------------------\n");
    uint8_t buffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (memoryUse)
    {
        readFile(sudoku, nameOfFile, verticalSeparator, horizontalSeparator);
        afficheurSudoku(sudoku, verticalSeparator, horizontalSeparator);
        getSquare(sudoku, 1, buffer);
        printBuffer(buffer);
        getRow(sudoku, 1, buffer);
        printBuffer(buffer);
        getColumn(sudoku, 1, buffer);
        printBuffer(buffer);
    }
    else
    {
        getSquareFROMFILE(nameOfFile, verticalSeparator, horizontalSeparator, 1, buffer);
        printBuffer(buffer);
        getSquareFROMFILE(nameOfFile, verticalSeparator, horizontalSeparator, 9, buffer);
        printBuffer(buffer);
        getSquareFROMFILE(nameOfFile, verticalSeparator, horizontalSeparator, 4, buffer);
        printBuffer(buffer);
    }
    return 0;
}
