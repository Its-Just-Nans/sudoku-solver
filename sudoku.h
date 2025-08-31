#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef DEF_SUDOKU_FUNCTION
#define DEF_SUDOKU_FUNCTION

#define N 9 // Size of the board (9x9)

typedef struct sudoku_t {
  uint8_t _grid[N][N];
} sudoku_t;

typedef struct sudoku_big_t {
  uint16_t _grid[N][N];
} sudoku_big_t;

#ifdef SUDOKU_ALLOW_PRIVATE
#define EXPOSED
uint8_t sudoku_char_to_num(const char temp);
bool sudoku_char_is_number(const char charac);
uint8_t sudoku_get_number(sudoku_t *sudoku, uint8_t row, uint8_t col);
void sudoku_set_number(sudoku_t *sudoku, uint8_t row, uint8_t col,
                       uint8_t value);
#else /* SUDOKU_ALLOW_PRIVATE */
#define EXPOSED inline static
#endif /* SUDOKU_ALLOW_PRIVATE */

void sudoku_print(sudoku_t *sudoku);
uint8_t sudoku_is_place_safe(sudoku_t *sudoku, uint8_t row, uint8_t col,
                             uint8_t num);
bool sudoku_solve_recursive(sudoku_t *sudoku);
bool sudoku_solve_iterative_limit(sudoku_t *sudoku, int max_iter);
bool sudoku_solve_iterative(sudoku_t *sudoku);
bool sudoku_read_from_csv(const char *filename, sudoku_t *sudoku,
                          unsigned int num_puzzle, sudoku_t *solution);
bool sudoku_verify(sudoku_t *sudoku);
bool sudoku_read(const char *filename, sudoku_t *sudoku);
bool sudoku_compare_grids(sudoku_t *sudoku, sudoku_t *solution);
void sudoku_empty_grid(sudoku_t *sudoku);
bool sudoku_is_valid_solved(sudoku_t *sudoku);
bool sudoku_from_line(sudoku_t *sudoku, const char *line);

#ifdef SUDOKU_BIG
void sudoku_empty_grid_b(sudoku_big_t *sudoku);
void sudoku_to_big(sudoku_t *sudoku, sudoku_big_t *sudoku_big);
void sudoku_to_normal(sudoku_big_t *sudoku_big, sudoku_t *sudoku);
#ifdef SUDOKU_ALLOW_PRIVATE
uint8_t sudoku_get_number_b(sudoku_big_t *sudoku, uint8_t row, uint8_t col);
void sudoku_set_number_b(sudoku_big_t *sudoku, uint8_t row, uint8_t col,
                         uint8_t value);
bool sudoku_get_number_hint(sudoku_big_t *sudoku, uint8_t row, uint8_t col,
                            uint8_t hint);
void sudoku_set_number_hint(sudoku_big_t *sudoku, uint8_t row, uint8_t col,
                            uint8_t hint);
void sudoku_remove_number_hint(sudoku_big_t *sudoku, uint8_t row, uint8_t col,
                               uint8_t hint);
bool sudoku_get_only_number_hint(sudoku_big_t *sudoku, uint8_t row, uint8_t col,
                                 uint8_t num);
#endif /* SUDOKU_ALLOW_PRIVATE */
#endif /* SUDOKU_BIG */
#endif /* DEF_SUDOKU_FUNCTION */