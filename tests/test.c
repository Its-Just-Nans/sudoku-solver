#define SUDOKU_BIG 1
#define SUDOKU_ALLOW_PRIVATE 1

#include "../sudoku.h"
#include <stdint.h>
#include <stdio.h>

#define test_print(fmt, ...) printf("\t[TEST]: " fmt, ##__VA_ARGS__)
#define run_test(func) run_test_impl(func, #func)
#define ERROR 255
#define CHECK(func_call)                                                       \
  do {                                                                         \
    int __ret = (func_call);                                                   \
    if (__ret == ERROR) {                                                      \
      return ERROR;                                                            \
    }                                                                          \
  } while (0)

void test_result(int return_code, const char *func_name) {
  if (return_code == ERROR) {
    printf("RESULT %s() failed\n", func_name);
  }
  printf("RESULT %s() succeed\n", func_name);
}

void run_test_impl(int (*func)(), const char *func_name) {
  printf("TESTING %s()\n", func_name);
  test_result(func(), func_name);
}

int test_csv() {
  sudoku_t board;
  sudoku_empty_grid(&board);
  sudoku_t solution;
  sudoku_empty_grid(&solution);

  const char *filename = "sudoku.csv";

  for (unsigned int i = 1; i <= 10; i++) {

    int result = sudoku_read_from_csv(filename, &board, i, &solution);

    if (result == -1) {
      test_print("Could not read file %s\n", filename);
      return -1;
    }

    if (!sudoku_solve_recursive(&board)) {
      test_print("ERROR: No solution %d exists!\n", i);
      return ERROR;
    }
    if (!sudoku_compare_grids(&board, &solution)) {
      test_print("ERROR: Solution %d is incorrect!\n", i);
      sudoku_print(&board);
      test_print("\n");

      sudoku_print(&solution);
      return ERROR;
    }
    test_print("Test passed: Solution %d is correct!\n", i);
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
      return 0;
    }
    test_print("ERROR: Could not read file %s\n", filename);
    return ERROR;
  }
  bool res = sudoku_compare_grids(&board, &solution);
  if (should_res != res) {
    sudoku_print(&board);
    test_print("\n");
    sudoku_print(&solution);
    return ERROR;
  }
  return 0;
}

int test_void_sudoku() {
  sudoku_t board;
  sudoku_empty_grid(&board);

  if (!sudoku_solve_iterative(&board)) {
    test_print("Cannot solve %s()\n", __func__);
    return ERROR;
  }
  if (!sudoku_is_valid_solved(&board)) {
    sudoku_print(&board);
    return ERROR;
  }
  return 0;
}

int test_single_sudoku(const char *filename) {
  sudoku_t board;
  sudoku_empty_grid(&board);
  bool read_re = sudoku_read(filename, &board);
  if (!read_re) {
    return ERROR;
  }
  sudoku_print(&board);

  if (!sudoku_solve_iterative(&board)) {
    test_print("Cannot solve %s()\n", __func__);
    return ERROR;
  }
  if (!sudoku_is_valid_solved(&board)) {
    sudoku_print(&board);
    return ERROR;
  }
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
      test_print("%s doesn't equals\n", buf);
      for (int i = 0; i < 15; i++) {
        test_print("%d", res[i]);
      }
      test_print("\n");
      return false;
    }
  }
  test_print("%s equals\n", buf);
  test_print();
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
    return ERROR;
  }
  sudoku_set_number_b(&board, row, col, 8);
  int res2[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res2, buf)) {
    return ERROR;
  }

  sudoku_set_number_hint(&board, row, col, 9);
  int res3[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res3, buf)) {
    return ERROR;
  }

  sudoku_remove_number_hint(&board, row, col, 9);
  int res4[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res4, buf)) {
    return ERROR;
  }

  sudoku_set_number_hint(&board, row, col, 8);
  int res_add_8[15] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res_add_8, buf)) {
    return ERROR;
  }
  if (!sudoku_get_only_number_hint(&board, row, col, 8)) {
    return ERROR;
  }
  sudoku_set_number_hint(&board, row, col, 9);
  if (sudoku_get_only_number_hint(&board, row, col, 9)) {
    return ERROR;
  }
  if (sudoku_get_only_number_hint(&board, row, col, 8)) {
    return ERROR;
  }
  sudoku_remove_number_hint(&board, row, col, 9);
  if (!sudoku_get_only_number_hint(&board, row, col, 8)) {
    return ERROR;
  }
  sudoku_remove_number_hint(&board, row, col, 7);
  sudoku_set_number_b(&board, row, col, 7);
  int res_set_number_7[15] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint16_to_hex(board._grid[row][col], buf);
  if (!compare_res_buf(res_set_number_7, buf)) {
    return ERROR;
  }

  return 0;
}

int test_read_sudoku_all() {
  const char *solution_line = "5......94..9....5..4....2...2.5..8....4..1.7.8.."
                              ".3...6..2..7.1..3.9.....6...4...8";
  CHECK(test_read_sudoku("sudoku.txt", solution_line, true, true));
  CHECK(test_read_sudoku("sudoku_single_line.txt", solution_line, true, true));
  CHECK(test_read_sudoku("sudoku_single_line_nospace.txt", solution_line, true,
                         true));
  CHECK(test_read_sudoku("sudoku_with_chars.txt", solution_line, true, true));
  CHECK(test_read_sudoku("sudoku_with_chars_2.txt", solution_line, true, true));
  // should fail
  CHECK(test_read_sudoku("sudoku_with_chars_missing_bug.txt", solution_line,
                         false, false));
  CHECK(test_read_sudoku("sudoku_with_chars_missing_random_bug.txt",
                         solution_line, false, false));
  CHECK(
      test_read_sudoku("sudoku_megaline_bug.txt", solution_line, false, false));
  return 0;
}

int main() {
  run_test(test_csv);
  run_test(test_read_sudoku_all);
  // test_single_sudoku("sudoku_impossible.txt");
  test_single_sudoku("sudoku_hard.txt");
  run_test(test_void_sudoku);
  test_sudoku_setter();
  return 0;
}