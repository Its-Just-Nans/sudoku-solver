#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef VERBOSE
#define printf(...) ;
#endif
#include "sudoku.h"

int main() {
  // Sample Sudoku puzzle (0 represents empty cells)
  int board[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0}};

  int solution[N][N] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}};

  // parse the CSV file
  const char *filename = "./tests/sudoku.csv";

  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("Could not open file %s\n", filename);
    return -1;
  }

  { // read first line of file
    char line[1024];
    if (fgets(line, sizeof(line), file) == NULL) {
      printf("Could not read first line \n");
      return -1;
    }
  }

  for (int i = 1; i <= 1; i++) {

    int result = readSudokusFromCSV(file, board, i, solution);
    if (result == -1) {
      printf("Could not read file %s\n", filename);
      return -1;
    }

    if (solveSudoku(board)) {
      if (checkSudoku(board, solution)) {
        printf("Solution %d is correct!\n", i);
      } else {
        printf("Solution %d is incorrect!\n", i);
        printBoard(board);
        printf("\n");
        printBoard(solution);
      }
    } else {
      printf("No solution %d exists!\n", i);
      exit(1);
    }
  }
  fclose(file);

  return 0;
}
