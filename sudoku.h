#include <stdbool.h>
#include <stdio.h>

#ifndef DEF_SUDOKU_FUNCTION

#define DEF_SUDOKU_FUNCTION

#define N 9 // Size of the board (9x9)
void printBoard(int board[N][N]);
bool isSafe(int board[N][N], int row, int col, int num);
bool solveSudoku(int board[N][N]);
int readSudokusFromCSV(FILE *restrict file, int board[N][N], int numPuzzles,
                       int solution[N][N]);
int checkSudoku(int board[N][N], int solution[N][N]);
#endif