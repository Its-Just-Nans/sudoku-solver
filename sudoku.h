#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef DEF_SUDOKU_FUNCTION
#define DEF_SUDOKU_FUNCTION

#define N 9 // Size of the board (9x9)

typedef struct sudoku_t {
  uint8_t grid[N][N];
} sudoku_t;

typedef struct sudoku_big_t {
  uint16_t grid[N][N];
} sudoku_big_t;

void sudoku_print(sudoku_t *sudoku);
uint8_t sudoku_is_place_safe(sudoku_t *sudoku, uint8_t row, uint8_t col,
                             uint8_t num);
bool solve_sudoku(sudoku_t *sudoku);
bool readSudokusFromCSV(const char *filename, sudoku_t *sudoku,
                        unsigned int num_puzzle, sudoku_t *solution);
bool verifySudoku(sudoku_t *sudoku);
bool read_sudoku(const char *filename, sudoku_t *sudoku);
bool sudoku_compare_grids(sudoku_t *sudoku, sudoku_t *solution);
void sudoku_empty_grid(sudoku_t *sudoku);
bool sudoku_is_valid_solved(sudoku_t *sudoku);
bool sudoku_from_line(sudoku_t *sudoku, const char *line);
void sudoku_to_big(sudoku_t *sudoku, sudoku_big_t *sudoku_big);
void sudoku_to_normal(sudoku_big_t *sudoku_big, sudoku_t *sudoku);

#endif /* DEF_SUDOKU_FUNCTION */