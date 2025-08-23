#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// #ifndef VERBOSE
// #define printf(...) ;
// #endif
#include "sudoku.h"

int main() {
  // Sample Sudoku puzzle (0 represents empty cells)
  sudoku_t board;
  sudoku_empty_grid(board);
  sudoku_t solution_board;
  sudoku_empty_grid(solution_board);

  // parse the CSV file
  const char *filename = "./tests/sudoku.csv";

  for (int num_puzzle = 1; num_puzzle <= 1; num_puzzle++) {

    uint8_t result =
        readSudokusFromCSV(filename, board, num_puzzle, solution_board);
    if (result != SUCCESS) {
      printf("Could not read file %s\n", filename);
      return 1;
    }
    sudoku_print_board(board);
    printf("---\n");

    if (solve_sudoku(board) == ERR) {
      printf("No solution %d exists!\n", num_puzzle);
      exit(1);
    }
    if (!sudoku_is_valid_solved(board) ||
        sudoku_compare_grids(board, solution_board) != SUCCESS) {
      printf("Solution %d is incorrect!\n", num_puzzle);
      sudoku_print_board(board);
      printf("\n");
      sudoku_print_board(solution_board);
      return 1;
    }
    sudoku_print_board(board);
    printf("---\n");
    printf("Solution %d is correct!\n", num_puzzle);
  }
  return 0;
}
