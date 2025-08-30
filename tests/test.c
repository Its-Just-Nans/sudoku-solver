#define SUDOKU_BIG 1
#define SUDOKU_ALLOW_PRIVATE 1

#include "../sudoku.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int test_csv() {
  sudoku_t board;
  sudoku_empty_grid(&board);
  sudoku_t solution;
  sudoku_empty_grid(&solution);

  const char *filename = "sudoku.csv";

  for (unsigned int i = 1; i <= 10; i++) {

    int result = sudoku_read_from_csv(filename, &board, i, &solution);

    if (result == -1) {
      printf("Could not read file %s\n", filename);
      return -1;
    }

    if (!sudoku_solve(&board)) {
      printf("ERROR: No solution %d exists!\n", i);
      exit(1);
    }
    if (!sudoku_compare_grids(&board, &solution)) {
      printf("ERROR: Solution %d is incorrect!\n", i);
      sudoku_print(&board);
      printf("\n");
      sudoku_print(&solution);
      exit(-1);
    }
    printf("Test passed: Solution %d is correct!\n", i);
  }
  return 0;
}

int test_read_sudoku(const char *filename, const char *solution_line,
                     bool should_read_res, bool should_res) {
  sudoku_t board;
  sudoku_empty_grid(&board);
  sudoku_t solution;
  sudoku_from_line(&solution, solution_line);

  bool read_re = sudoku_read(filename, &board);
  if (!read_re) {
    if (read_re == should_read_res) {
      printf("Test passed for %s - could not read file\n", filename);
      return 0;
    }
    printf("ERROR: Could not read file %s\n", filename);
    return -1;
  }
  bool res = sudoku_compare_grids(&board, &solution);
  if (should_res != res) {
    printf("ERROR: Test %s(\"%s\") failed\n", __func__, filename);
    sudoku_print(&board);
    printf("\n");
    sudoku_print(&solution);
    exit(1);
    return -1;
  }
  printf("Test passed for %s(\"%s\")\n", __func__, filename);
  return 0;
}

int test_void_sudoku() {
  sudoku_t board;
  sudoku_empty_grid(&board);

  if (!sudoku_solve_iterative(&board)) {
    printf("Cannot solve %s()\n", __func__);
    exit(1);
  }
  if (!sudoku_is_valid_solved(&board)) {
    printf("Test %s() failed\n", __func__);
    sudoku_print(&board);
    exit(1);
  }
  printf("Test passed for %s()\n", __func__);
  return 0;
}

int test_single_sudoku(const char *filename) {
  sudoku_t board;
  sudoku_empty_grid(&board);
  bool read_re = sudoku_read(filename, &board);
  if (!read_re) {
    printf("Test %s() failed\n", __func__);
    exit(1);
  }
  sudoku_print(&board);

  if (!sudoku_solve_iterative(&board)) {
    printf("Cannot solve %s()\n", __func__);
    exit(1);
  }
  if (!sudoku_is_valid_solved(&board)) {
    printf("Test %s() failed\n", __func__);
    sudoku_print(&board);
    exit(1);
  }
  printf("Test passed for %s()\n", __func__);
  return 0;
}

void uint16_to_hex(uint16_t value, char *buffer) {
  for (int i = 0; i < 15; i++) {
    buffer[i] = (value & (1u << i)) ? '1' : '0';
  }
  buffer[15] = '\0'; // null terminator
}

bool compare_res_buf(const int *res, const char *buf) {
  for (int i = 0; i < 15; i++) {
    int bit_from_buf = (buf[i] == '1') ? 1 : 0;
    if (res[i] != bit_from_buf) {
      printf("%s doesn't equal\n", buf);
      for (int i = 0; i < 15; i++) {
        printf("%d", res[i]);
      }
      printf("\n");
      return false;
    }
  }
  printf("%s equal\n", buf);
  for (int i = 0; i < 15; i++) {
    printf("%d", res[i]);
  }
  printf("\n");
  return true;
}

int test_sudoku_setter() {
  char buf[16] = "000000000000000"; // 15 + '\0'
  uint8_t row = 0;
  uint8_t col = 0;
  sudoku_big_t board;
  sudoku_empty_grid_b(&board);
  int res[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  if (!compare_res_buf(res, buf)) {
    printf("Test %s() failed\n", __func__);
    exit(1);
  }
  sudoku_set_number_b(&board, row, col, 8);
  int res2[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res2, buf)) {
    printf("Test %s() failed\n", __func__);
    exit(1);
  }

  sudoku_set_number_hint(&board, row, col, 9);
  int res3[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res3, buf)) {
    printf("Test %s() failed\n", __func__);
    exit(1);
  }

  sudoku_remove_number_hint(&board, row, col, 9);
  int res4[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res4, buf)) {
    printf("Test %s() failed\n", __func__);
    exit(1);
  }
  printf("Test passed for %s()\n", __func__);
  return 0;
}

int main() {
  test_csv();
  const char *solution_line = "5......94..9....5..4....2...2.5..8....4..1.7.8.."
                              ".3...6..2..7.1..3.9.....6...4...8";
  test_read_sudoku("sudoku.txt", solution_line, true, true);
  test_read_sudoku("sudoku_single_line.txt", solution_line, true, true);
  test_read_sudoku("sudoku_single_line_nospace.txt", solution_line, true, true);
  test_read_sudoku("sudoku_with_chars.txt", solution_line, true, true);
  test_read_sudoku("sudoku_with_chars_2.txt", solution_line, true, true);
  // should fail
  test_read_sudoku("sudoku_with_chars_missing_bug.txt", solution_line, false,
                   false);
  test_read_sudoku("sudoku_with_chars_missing_random_bug.txt", solution_line,
                   false, false);
  test_read_sudoku("sudoku_megaline_bug.txt", solution_line, false, false);
  // test_single_sudoku("sudoku_impossible.txt");
  test_single_sudoku("sudoku_hard.txt");
  test_void_sudoku();
  test_sudoku_setter();
  return 0;
}