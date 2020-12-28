#include <stdio.h>
#include <stdint.h>

int leftByte(uint8_t* byte);
int rightByte(uint8_t* byte);
void readFile(uint8_t sudoku[9][9][9], uint8_t* nameOfFile, char* vSeparator, char* hSeparator);
void afficheurSudoku(uint8_t sudoku[9][9][9], char* vSeparator, char* hSeparator);