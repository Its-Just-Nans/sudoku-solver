#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifndef VERBOSE
#define printf(...) ;
#endif

#ifndef DEF_SUDOKU_FUNCTION
#define DEF_SUDOKU_FUNCTION

#define N 9 // Size of the board (9x9)
typedef uint8_t sudoku_t[N][N];
typedef uint16_t sudoku_big_t[N][N];

void sudoku_print_board(sudoku_t board);
uint8_t sudoku_is_place_safe(sudoku_t board, uint8_t row, uint8_t col,
                             uint8_t num);
bool solve_sudoku(sudoku_t board);
bool readSudokusFromCSV(const char *filename, sudoku_t board,
                        unsigned int num_puzzle, sudoku_t solution);
bool verifySudoku(sudoku_t board);
bool read_sudoku(const char *filename, sudoku_t board);
bool sudoku_compare_grids(sudoku_t board, sudoku_t solution);
void sudoku_empty_grid(sudoku_t sudoku);
bool sudoku_is_valid_solved(sudoku_t sudoku);
bool sudoku_from_line(sudoku_t sudoku, const char *line);
void sudoku_to_big(sudoku_t sudoku, sudoku_big_t sudoku_big);
void sudoku_to_normal(sudoku_big_t sudoku_big, sudoku_t sudoku);

#endif /* DEF_SUDOKU_FUNCTION */