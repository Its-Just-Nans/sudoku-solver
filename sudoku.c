
#include "sudoku.h"
#include <stdint.h>
#include <stdio.h>

#ifdef SUDOKU_VERBOSE
#define SUDOKU_LOG(fmt, ...) printf("SUDOKU_LOG: " fmt, ##__VA_ARGS__)
#else
#define SUDOKU_LOG(fmt, ...) ((void)0)
#endif

EXPOSED uint8_t sudoku_char_to_num(const char temp) {
  return (uint8_t)(temp - '0');
}

EXPOSED bool sudoku_char_is_number(const char charac) {
  return charac >= '0' && charac <= '9';
}

EXPOSED uint8_t sudoku_get_number(sudoku_t *sudoku, uint8_t row, uint8_t col) {
  return sudoku->_grid[row][col];
}

EXPOSED void sudoku_set_number(sudoku_t *sudoku, uint8_t row, uint8_t col,
                               uint8_t value) {
  sudoku->_grid[row][col] = value;
}

/// | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
/// |:-------------:|:---------------------------------------------------:|
/// |  number 0-9   |              bit flags of possibility               |
EXPOSED uint8_t sudoku_get_number_b(sudoku_big_t *sudoku, uint8_t row,
                                    uint8_t col) {
  uint16_t temp = sudoku->_grid[row][col] << 12;
  return (uint8_t)(temp >> 12);
  // return (uint8_t)(sudoku[row][col] & 0xF);
}

EXPOSED bool sudoku_get_number_hint(sudoku_big_t *sudoku, uint8_t row,
                                    uint8_t col, uint8_t hint) {
  if (hint < 1 || hint > 9) {
    return false; // only digits 1–9 valid
  }
  uint16_t cell = sudoku->_grid[row][col];
  return (cell >> (hint + 3)) & 1;
}

EXPOSED void sudoku_set_number_hint(sudoku_big_t *sudoku, uint8_t row,
                                    uint8_t col, uint8_t hint) {

  if (hint < 1 || hint > 9) {
    return;
  }
  sudoku->_grid[row][col] |= (1 << (hint + 3));
}

EXPOSED void sudoku_remove_number_hint(sudoku_big_t *sudoku, uint8_t row,
                                       uint8_t col, uint8_t hint) {
  if (hint < 1 || hint > 9) {
    return;
  }
  sudoku->_grid[row][col] &= ~(uint16_t)(1 << (hint + 3));
}

EXPOSED bool sudoku_get_only_number_hint(sudoku_big_t *sudoku, uint8_t row,
                                         uint8_t col, uint8_t num) {
  if (num < 1 || num > 9)
    return false;

  uint16_t cell = sudoku->_grid[row][col];

  // extract only hint bits (bits 4–12)
  uint16_t hints = cell & 0x1FF0;

  // check if exactly one bit set
  if (hints == (1u << (num + 3))) {
    return true;
  }
  return false;
}

EXPOSED void sudoku_set_number_b(sudoku_big_t *sudoku, uint8_t row, uint8_t col,
                                 uint8_t value) {
  uint16_t cell = sudoku->_grid[row][col];

  // 1. Clear old number (low 4 bits)
  cell &= 0xFFF0;

  // 2. Set new number
  cell |= (value & 0xF);

  // 3. Clear all old hints
  cell &= 0x000F;
  sudoku->_grid[row][col] = cell;

  // sudoku[row][col] = (sudoku[row][col] & 0xFFF0) | (value & 0xF);
  for (row = 0; row < N; row++) {
  }
}

// Function to print the Sudoku board
void sudoku_print(sudoku_t *sudoku) {
  for (uint8_t row = 0; row < N; row++) {
    for (uint8_t col = 0; col < N; col++) {
      printf("%d ", sudoku_get_number(sudoku, row, col));
    }
    printf("\n");
  }
}

// Function to check if it's safe to place a number at a given position
uint8_t sudoku_is_place_safe(sudoku_t *sudoku, uint8_t row, uint8_t col,
                             uint8_t num) {
  // Check if the number exists in the col
  for (uint8_t col_num = 0; col_num < N; col_num++) {
    if (sudoku_get_number(sudoku, row, col_num) == num) {
      return false;
    }
  }

  // Check if the number exists in the row
  for (uint8_t row_num = 0; row_num < N; row_num++) {
    if (sudoku_get_number(sudoku, row_num, col) == num) {
      return false;
    }
  }

  // Check if the number exists in the 3x3 subgrid
  uint8_t startRow = row - row % 3;
  uint8_t startCol = col - col % 3;
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      if (sudoku_get_number(sudoku, i + startRow, j + startCol) == num) {
        return false;
      }
    }
  }

  return true;
}

bool sudoku_is_solved(sudoku_t *sudoku, uint8_t *row, uint8_t *col) {
  for (*row = 0; (*row) < N; (*row)++) {
    for (*col = 0; (*col) < N; (*col)++) {
      if (sudoku_get_number(sudoku, *row, *col) == 0) {
        return false;
      }
    }
  }
  return true;
}

// Backtracking function to solve the Sudoku
bool sudoku_solve_recursive(sudoku_t *sudoku) {
  uint8_t row, col;

  if (sudoku_is_solved(sudoku, &row, &col)) {
    return true;
  }

  // Try numbers 1 to 9 for the empty cell
  for (uint8_t num = 1; num <= N; num++) {
    if (sudoku_is_place_safe(sudoku, row, col, num)) {
      sudoku_set_number(sudoku, row, col, num);

      // Recursively attempt to solve with the current number
      if (sudoku_solve_recursive(sudoku) == true) {
        return true;
      }

      // If placing num doesn't lead to a solution, backtrack
      sudoku_set_number(sudoku, row, col, 0);
    }
  }
  return false;
}

bool sudoku_solve_iterative(sudoku_t *sudoku) {
  return sudoku_solve_iterative_limit(sudoku, N * N * N * N * N * N);
}

bool sudoku_solve_iterative_limit(sudoku_t *sudoku, int max_iter) {
  uint8_t row = 0, col = 0;

  // Flatten empty cells into a list for easier navigation
  uint8_t empty_cells[N * N][2];
  uint8_t empty_count = 0;

  for (row = 0; row < N; row++) {
    for (col = 0; col < N; col++) {
      uint8_t num = sudoku_get_number(sudoku, row, col);
      if (num == 0) {
        empty_cells[empty_count][0] = row;
        empty_cells[empty_count][1] = col;
        empty_count++;
      }
    }
  }
  int nb_iter = 0;
  int idx = 0; // index in empty_cells[]
  while (idx >= 0 && idx < empty_count) {
    row = empty_cells[idx][0];
    col = empty_cells[idx][1];
    uint8_t placed = sudoku_get_number(sudoku, row, col);
    bool found = false;

    // Try next number after the last tried
    for (uint8_t num = placed + 1; num <= N; num++) {
      if (sudoku_is_place_safe(sudoku, row, col, num)) {
        sudoku_set_number(sudoku, row, col, num);
        found = true;
        break;
      }
    }

    if (found) {
      // Move forward
      idx++;
    } else {
      // Reset and backtrack
      sudoku_set_number(sudoku, row, col, 0);
      idx--;
    }
    if (nb_iter++ > max_iter) {
      break;
    }
  }
  return (idx == empty_count); // solved if we placed all successfully
}

bool sudoku_solve_iterative_limit_b(sudoku_big_t *sudoku, int max_iter) {
  uint8_t row = 0, col = 0;

  // Flatten empty cells into a list for easier navigation
  uint8_t empty_cells[N * N][2];
  uint8_t empty_count = 0;

  for (row = 0; row < N; row++) {
    for (col = 0; col < N; col++) {
      uint8_t num = sudoku_get_number_b(sudoku, row, col);
      if (num == 0) {
        empty_cells[empty_count][0] = row;
        empty_cells[empty_count][1] = col;
        empty_count++;
      }
    }
  }
  bool force = false;
  int nb_iter = 0;
  int idx = 0; // index in empty_cells[]
  while (idx >= 0 && idx < empty_count) {
    row = empty_cells[idx][0];
    col = empty_cells[idx][1];
    uint8_t placed = sudoku_get_number_b(sudoku, row, col);
    bool found = false;

    // Try next number after the last tried
    for (uint8_t num = placed + 1; num <= N; num++) {
      if (sudoku_get_only_number_hint(sudoku, row, col, num)) {
        sudoku_set_number_b(sudoku, row, col, num);
        found = true;
        break;
      } else if (force && sudoku_get_number_hint(sudoku, row, col, num)) {
        found = true;
        break;
      }
    }

    if (found) {
      // Move forward
      idx++;
    } else {
      // Reset and backtrack
      sudoku_set_number_b(sudoku, row, col, 0);
      idx--;
    }
    if (nb_iter++ > max_iter) {
      break;
    }
  }
  return (idx == empty_count); // solved if we placed all successfully
}

void get_split(const char *line, int idx, char *res) {
  int i = 0;
  int j = 0;
  int comma_count = 0;

  while (line[i] != '\0') {
    if (line[i] == ',' && comma_count == idx) {
      res[j] = '\0';
      return;
    }

    if (line[i] == ',') {
      comma_count++;
      i++;
      if (comma_count == idx) {
        j = 0;
      }
    }

    if (comma_count == idx) {
      res[j++] = line[i];
    }

    i++;
  }

  res[j] = '\0';
}

bool sudoku_read_from_csv(const char *filename, sudoku_t *sudoku,
                          unsigned int num_puzzle, sudoku_t *solution) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    SUDOKU_LOG("Could not open file %s\n", filename);
    return false;
  }
  char line[1024];
  char temp[N * N + 1];
  unsigned int puzzle_index = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (puzzle_index != num_puzzle) {
      puzzle_index++;
      continue;
    }
    if (puzzle_index > num_puzzle) {
      SUDOKU_LOG("Could not read line %d\n", num_puzzle);
      return false;
    }
    // Skip the ID (first token)
    get_split(line, 1, temp);
    // Read puzzle into the 2D array
    sudoku_from_line(sudoku, temp);
    get_split(line, 2, temp);
    // Read the solution into the 2D array
    sudoku_from_line(solution, temp);
    puzzle_index++;
    fclose(file);
    return true;
  }
  fclose(file);
  SUDOKU_LOG("Could not read file\n");
  return false;
}

bool sudoku_compare_grids(sudoku_t *sudoku, sudoku_t *solution) {
  for (uint8_t row = 0; row < N; row++) {
    for (uint8_t col = 0; col < N; col++) {
      if (sudoku_get_number(sudoku, row, col) !=
          sudoku_get_number(solution, row, col)) {
        SUDOKU_LOG("Incorrect number at %d %d\n", row, col);
        return false;
      }
    }
  }
  return true;
}

bool sudoku_read(const char *filename, sudoku_t *sudoku) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    SUDOKU_LOG("Could not open file %s\n", filename);
    return false;
  }
  char temp[2] = "\0\0";
  uint8_t inserted = 81;
  uint8_t max_col = N;
  for (uint8_t line_number = 0; line_number < N;) {
    for (uint8_t col_number = 0; col_number < max_col;) {
      if (temp[0] == '\0') {
        if (fgets(temp, 2, file) == NULL) {
          fclose(file);
          SUDOKU_LOG("Error reading file\n");
          return false; // error or EOF
        }
      }
      if (sudoku_char_is_number(temp[0])) {
        sudoku_set_number(sudoku, line_number, col_number++,
                          sudoku_char_to_num(temp[0]));
        inserted--;
        if (inserted % N == 0) {
          line_number++;
          break;
        }
      } else {
        max_col++;
      }
      if (max_col > 81) {
        // define a limit to avoid infinite loops
        fclose(file);
        return false;
      }
      temp[0] = '\0';
    }
    if (inserted == 0) {
      break;
    }
    if (fgets(temp, 2, file) == NULL) {
      fclose(file);
      return 1; // error or EOF
    }
    if (temp[0] == '\n' || !sudoku_char_is_number(temp[0])) {
      temp[0] = '\0';
    }
    max_col = N;
  }
  fclose(file);
  return true;
}

bool sudoku_verify(sudoku_t *sudoku) {
  uint8_t row, col;
  if (!sudoku_is_solved(sudoku, &row, &col)) {
    return false;
  }
  // todo check numbers
  return true;
}

void sudoku_empty_grid(sudoku_t *sudoku) {
  for (uint8_t row = 0; row < N; row++) {
    for (uint8_t col = 0; col < N; col++) {
      sudoku_set_number(sudoku, row, col, 0);
    }
  }
}

void sudoku_empty_grid_b(sudoku_big_t *sudoku) {
  for (uint8_t row = 0; row < N; row++) {
    for (uint8_t col = 0; col < N; col++) {
      sudoku_set_number_b(sudoku, row, col, 0);
    }
  }
}

bool sudoku_is_valid_solved(sudoku_t *sudoku) {
  int seen[10]; // index 1-9 used

  // Check rows
  for (uint8_t row = 0; row < 9; row++) {
    for (int i = 1; i <= 9; i++)
      seen[i] = 0;
    for (uint8_t col = 0; col < 9; col++) {
      uint8_t num = sudoku_get_number(sudoku, row, col);
      if (num == 0)
        continue; // allow blanks
      if (num > 9 || seen[num])
        return 0;
      seen[num] = 1;
    }
  }

  // Check columns
  for (uint8_t col = 0; col < 9; col++) {
    for (int i = 1; i <= 9; i++)
      seen[i] = 0;
    for (uint8_t row = 0; row < 9; row++) {
      uint8_t num = sudoku_get_number(sudoku, row, col);
      if (num == 0)
        continue;
      if (num > 9 || seen[num])
        return 0;
      seen[num] = 1;
    }
  }

  // Check 3x3 subgrids
  for (uint8_t boxRow = 0; boxRow < 3; boxRow++) {
    for (uint8_t boxCol = 0; boxCol < 3; boxCol++) {
      for (uint8_t i = 1; i <= 9; i++)
        seen[i] = 0;
      for (uint8_t r = 0; r < 3; r++) {
        for (uint8_t c = 0; c < 3; c++) {
          uint8_t row_num = (uint8_t)(boxRow * 3 + r);
          uint8_t col_num = (uint8_t)(boxCol * 3 + c);
          uint8_t num = sudoku_get_number(sudoku, row_num, col_num);
          if (num == 0)
            continue;
          if (num > 9 || seen[num])
            return 0;
          seen[num] = 1;
        }
      }
    }
  }

  return 1; // valid Sudoku
}

bool sudoku_from_line(sudoku_t *sudoku, const char *line) {
  if (line == NULL) {
    SUDOKU_LOG("Error line is NULL\n");
    return false;
  }
  size_t pos = 0;

  for (uint8_t row = 0; row < 9; row++) {
    for (uint8_t col = 0; col < 9; col++) {
      char ch = line[pos++];
      uint8_t num = 0;

      if (ch == '.') {
        num = 0;
      } else if (sudoku_char_is_number(ch)) {
        num = sudoku_char_to_num(ch);
      } else {
        return false;
      }

      sudoku_set_number(sudoku, row, col, num);
    }
  }
  return true;
}

void sudoku_to_big(sudoku_t *sudoku, sudoku_big_t *sudoku_big) {
  for (uint8_t row = 0; row < 9; row++) {
    for (uint8_t col = 0; col < 9; col++) {
      sudoku_set_number_b(sudoku_big, row, col,
                          sudoku_get_number(sudoku, row, col));
    }
  }
}

void sudoku_to_normal(sudoku_big_t *sudoku_big, sudoku_t *sudoku) {
  for (uint8_t row = 0; row < 9; row++) {
    for (uint8_t col = 0; col < 9; col++) {
      sudoku_set_number(sudoku, row, col,
                        sudoku_get_number_b(sudoku_big, row, col));
    }
  }
}