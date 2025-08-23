#include "../sudoku.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t skipFirstLine(FILE *file) {
  char temp[2] = "\0\0";
  while (fgets(temp, 2, file) != NULL) {
    if (temp[0] == '\n') {
      return ERR;
    }
  }
  return SUCCESS;
}

int test_csv() {
  sudoku_t board;
  sudoku_empty_grid(board);
  sudoku_t solution;
  sudoku_empty_grid(solution);

  const char *filename = "sudoku.csv";

  for (int i = 1; i <= 10; i++) {

    int result = readSudokusFromCSV(filename, board, i, solution);

    if (result == -1) {
      printf("Could not read file %s\n", filename);
      return -1;
    }

    if (solve_sudoku(board) == SUCCESS) {
      if (sudoku_compare_grids(board, solution) == SUCCESS) {
        printf("Solution %d is correct!\n", i);
      } else {
        printf("Solution %d is incorrect!\n", i);
        sudoku_print_board(board);
        printf("\n");
        sudoku_print_board(solution);
      }
    } else {
      printf("No solution %d exists!\n", i);
      exit(1);
    }
  }
  return 0;
}

int test_read_csv(const char *filename, const char *solution_line,
                  int should_res) {
  sudoku_t board;
  sudoku_empty_grid(board);
  sudoku_t solution;
  sudoku_from_line(solution, solution_line);

  int res_read = read_sudoku(filename, board);
  if (res_read) {
    if (should_res == -1) {
      printf("Test passed for %s - could not read file\n", filename);
      return 0;
    }
    printf("Could not read file %s\n", filename);
    return -1;
  }
  int res = sudoku_compare_grids(board, solution);
  if (should_res != res) {
    printf("Test readSudoku(\"%s\") failed\n", filename);
    sudoku_print_board(board);
    printf("\n");
    sudoku_print_board(solution);
    exit(1);
    return -1;
  }
  printf("Test passed for %s(\"%s\")\n", __func__, filename);
  return 0;
}

int test_void_sudoku() {
  sudoku_t board;
  sudoku_empty_grid(board);

  if (solve_sudoku(board) != SUCCESS) {
    printf("Cannot solve %s()\n", __func__);
    exit(1);
  }
  if (!sudoku_is_valid_solved(board)) {
    printf("Test %s() failed\n", __func__);
    sudoku_print_board(board);
    exit(1);
  }
  printf("Test passed for %s()\n", __func__);
  return 0;
}

int main() {
  printf("Running test_csv()\n");
  test_csv();
  printf("Running test_read_csv()\n");
  const char *solution_line = "5......94..9....5..4....2...2.5..8....4..1.7.8.."
                              ".3...6..2..7.1..3.9.....6...4...8";
  test_read_csv("sudoku.txt", solution_line, 0);
  test_read_csv("sudoku_single_line.txt", solution_line, 0);
  test_read_csv("sudoku_single_line_nospace.txt", solution_line, 0);
  test_read_csv("sudoku_with_chars.txt", solution_line, 0);
  test_read_csv("sudoku_with_chars_2.txt", solution_line, 0);
  // should fail
  test_read_csv("sudoku_with_chars_missing_bug.txt", solution_line, -1);
  test_read_csv("sudoku_with_chars_missing_random_bug.txt", solution_line, -1);
  test_read_csv("sudoku_megaline_bug.txt", solution_line, -1);

  test_void_sudoku();
  return 0;
}