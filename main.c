#include "sudoku.h"

uint8_t main(int argc, char *argv[]){
    char *outputName = "sudokuValid.txt";
    char *verticalSeparator = "|";
    char *horizontalSeparator = "=";
    char *nameOfFile = "sudoku2.txt";
    for(uint8_t o=1; o<argc; o++){
        if(argv[o][0] == '-'){
            if(argv[o][1] == 'o'){
                o++;
                outputName = argv[o];
            }else if(argv[o][1] == 's'){
                if(argv[o][2] == 'v'){
                    o++;
                    verticalSeparator = argv[o];
                }else if(argv[o][2] == 'h'){
                    o++;
                    horizontalSeparator = argv[o];
                }
            }
        }else{
            nameOfFile = argv[o];
        }
    }
    printf("-------Options-----\n");
    printf("outputName -> '%s'\n", outputName);
    printf("verticalSeparator -> '%s'\n", verticalSeparator);
    printf("horizontalSeparator -> '%s'\n", horizontalSeparator);
    printf("Entry file -> '%s'\n", nameOfFile);
    printf("-------------------\n");
    uint16_t sudoku[9][9][1];
    readFile(sudoku, nameOfFile, verticalSeparator, horizontalSeparator);
    afficheurSudoku(sudoku, verticalSeparator, horizontalSeparator);
    return 0;
}
