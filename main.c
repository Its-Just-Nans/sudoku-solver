#include "sudoku.h"



uint8_t main(int argc, char *argv[]){
    printf("Arguments : \n");
    char *outputName = "sudokuValid.txt";
    char *verticalSeparator = "=";
    char *horizontalSeparator = "|";
    char *nameOfFile = "sudoku2.txt";
    for(int o=0; o< argc; o++){
        printf("%s\n", argv[o]);
        if(argv[o][0] == '-'){
            if(argv[o][1] == 'o'){
                outputName = argv[o+1];
            }else if(argv[o][1] == 's'){
                if(argv[o][2] == 'v'){
                    verticalSeparator = argv[o+1];
                }else if(argv[o][2] == 'h'){
                    horizontalSeparator = argv[o+1];
                }
            }else if(argv[o][1] == 'e'){

            }
        }
    }
    
    printf("-------Options-----\n");
    printf("outputName = %s\n", outputName);
    printf("verticalSeparator = %s\n", verticalSeparator);
    printf("horizontalSeparator = %s\n", horizontalSeparator);
    printf("Entry file = %s\n", nameOfFile);
    printf("-------------\n");
    uint8_t sudoku[9][9][9];
    readFile(sudoku, nameOfFile, verticalSeparator, horizontalSeparator);
    afficheurSudoku(sudoku, verticalSeparator, horizontalSeparator);
    return 0;
}
