#include "sudoku.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Sample Sudoku puzzle (0 represents empty cells)
  sudoku_t board;
  sudoku_empty_grid(&board);
  sudoku_t solution_board;
  sudoku_empty_grid(&solution_board);

  // parse the CSV file
  const char *filename = "./tests/sudoku.csv";

  for (unsigned int num_puzzle = 1; num_puzzle <= 1; num_puzzle++) {

    uint8_t result =
        sudoku_read_from_csv(filename, &board, num_puzzle, &solution_board);
    if (!result) {
      printf("Could not read file %s\n", filename);
      return 1;
    }
    sudoku_print(&board);
    printf("---\n");

    if (!sudoku_solve(&board)) {
      printf("No solution %d exists!\n", num_puzzle);
      exit(1);
    }
    if (!sudoku_is_valid_solved(&board) ||
        !sudoku_compare_grids(&board, &solution_board)) {
      printf("Solution %d is incorrect!\n", num_puzzle);
      sudoku_print(&board);
      printf("\n");
      sudoku_print(&solution_board);
      return 1;
    }
    sudoku_print(&board);
    printf("---\n");
    printf("Solution %d is correct!\n", num_puzzle);
  }
  return 0;
}
