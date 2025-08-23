#include <stdint.h>
#include <stdio.h>
#ifndef VERBOSE
#define printf(...) ;
#endif

#ifndef DEF_SUDOKU_FUNCTION
#define DEF_SUDOKU_FUNCTION

enum return_code { SUCCESS = 0, ERR, ERR_FILE };

#define N 9 // Size of the board (9x9)
typedef uint8_t sudoku_t[N][N];

void sudoku_print_board(sudoku_t board);
uint8_t sudoku_is_place_safe(sudoku_t board, uint8_t row, uint8_t col,
                             uint8_t num);
uint8_t solve_sudoku(sudoku_t board);
uint8_t readSudokusFromCSV(const char *filename, sudoku_t board,
                           unsigned int num_puzzle, sudoku_t solution);
uint8_t verifySudoku(sudoku_t board);
uint8_t read_sudoku(const char *filename, sudoku_t board);
uint8_t sudoku_compare_grids(sudoku_t board, sudoku_t solution);
uint8_t sudoku_get_number(sudoku_t sudoku, uint8_t row, uint8_t col);
uint8_t sudoku_set_number(sudoku_t sudoku, uint8_t row, uint8_t col,
                          uint8_t value);
void sudoku_empty_grid(sudoku_t sudoku);
int sudoku_is_valid_solved(sudoku_t sudoku);
int sudoku_from_line(sudoku_t sudoku, const char *line);

#endif /* DEF_SUDOKU_FUNCTION */