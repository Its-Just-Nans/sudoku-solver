#include "sudoku.h"

uint8_t main(int argc, char *argv[]){
    char *outputName = "sudokuValid.txt";
    char *verticalSeparator = "|";
    char *horizontalSeparator = "=";
    char *nameOfFile = "sudoku.txt";
    for(uint8_t count=1; count<argc; count++){
        if(argv[count][0] == '-'){
            if(argv[count][1] == 'o'){
                count++;
                outputName = argv[count];
            }else if(argv[count][1] == 's'){
                if(argv[count][2] == 'v'){
                    count++;
                    verticalSeparator = argv[count];
                }else if(argv[count][2] == 'h'){
                    count++;
                    horizontalSeparator = argv[count];
                }
            }
        }else{
            nameOfFile = argv[count];
        }
    }
    printf("-------Options-----\n");
    printf("outputName -> '%s'\n", outputName);
    printf("verticalSeparator -> '%s'\n", verticalSeparator);
    printf("horizontalSeparator -> '%s'\n", horizontalSeparator);
    printf("Entry file -> '%s'\n", nameOfFile);
    printf("-------------------\n");
    uint16_t sudoku[9][9][1] ={{{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
                                {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}};
    printf("Sudoku size : %d bytes or %d bits\n", sizeof(sudoku), sizeof(sudoku)*8);
    //afficheurSudoku(sudoku, verticalSeparator, horizontalSeparator);
    readFile(sudoku, nameOfFile, verticalSeparator, horizontalSeparator);
    afficheurSudoku(sudoku, verticalSeparator, horizontalSeparator);
    uint8_t option = 1;
    uint8_t buffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    getRow(sudoku, nameOfFile, &option, 1, buffer);
    for(uint8_t count = 0;count<9;count++){
        printf("%d ", buffer[count]);
    }
    printf("\nbuffer printed\n");
    return 0;
}
