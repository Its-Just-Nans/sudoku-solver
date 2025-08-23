
#include "sudoku.h"

uint8_t char_to_num(const char temp) { return temp - '0'; }

uint8_t char_is_number(const char number) {
  return (number >= '0' && number <= '9') ? 1 : 0;
}

// Function to print the Sudoku board
void sudoku_print_board(sudoku_t board) {
  for (uint8_t row = 0; row < N; row++) {
    for (uint8_t col = 0; col < N; col++) {
      printf("%d ", sudoku_get_number(board, row, col));
    }
    printf("\n");
  }
}

// Function to check if it's safe to place a number at a given position
uint8_t sudoku_is_place_safe(sudoku_t board, uint8_t row, uint8_t col,
                             uint8_t num) {
  // Check if the number exists in the col
  for (uint8_t col_num = 0; col_num < N; col_num++) {
    if (sudoku_get_number(board, row, col_num) == num) {
      return ERR;
    }
  }

  // Check if the number exists in the row
  for (uint8_t row_num = 0; row_num < N; row_num++) {
    if (sudoku_get_number(board, row_num, col) == num) {
      return ERR;
    }
  }

  // Check if the number exists in the 3x3 subgrid
  uint8_t startRow = row - row % 3;
  uint8_t startCol = col - col % 3;
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      if (sudoku_get_number(board, i + startRow, j + startCol) == num) {
        return ERR;
      }
    }
  }

  return SUCCESS;
}

uint8_t sudoku_is_solved(sudoku_t board, uint8_t *row, uint8_t *col) {
  for (*row = 0; (*row) < N; (*row)++) {
    for (*col = 0; (*col) < N; (*col)++) {
      if (sudoku_get_number(board, *row, *col) == 0) {
        return ERR;
      }
    }
  }
  return SUCCESS;
}

// Backtracking function to solve the Sudoku
uint8_t solve_sudoku(sudoku_t board) {
  uint8_t row, col;

  if (sudoku_is_solved(board, &row, &col) == SUCCESS) {
    return SUCCESS;
  }

  // Try numbers 1 to 9 for the empty cell
  for (uint8_t num = 1; num <= N; num++) {
    if (sudoku_is_place_safe(board, row, col, num) == SUCCESS) {
      sudoku_set_number(board, row, col, num);

      // Recursively attempt to solve with the current number
      if (solve_sudoku(board) == SUCCESS) {
        return SUCCESS;
      }

      // If placing num doesn't lead to a solution, backtrack
      sudoku_set_number(board, row, col, 0);
    }
  }

  return ERR;
}
void get_splitted(const char *line, int idx, char *res) {
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

uint8_t readSudokusFromCSV(const char *filename, sudoku_t board,
                           unsigned int num_puzzle, sudoku_t solution) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("Could not open file %s\n", filename);
    return ERR_FILE;
  }
  char line[1024];
  char temp[N * N + 1];
  int puzzle_index = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (puzzle_index != num_puzzle) {
      puzzle_index++;
      continue;
    }
    if (puzzle_index > num_puzzle) {
      printf("Could not read line %d\n", num_puzzle);
      return ERR;
    }

    // Read the line (excluding the ID) and parse the puzzle
    uint8_t num;
    int i = 0;
    // Skip the ID (first token)
    get_splitted(line, 1, temp);

    // Read puzzle into the 2D array
    while (temp[i] != '\0' && i < N * N) {
      if (temp[i] == '.') {
        num = 0;
      } else {
        if (!char_is_number(temp[i])) {
          return ERR;
        }
        num = char_to_num(temp[i]);
      }
      sudoku_set_number(board, i / N, i % N, num);
      i++;
    }
    get_splitted(line, 2, temp);

    // Read the solution into the 2D array
    if (solution != NULL) {
      i = 0;
      while (temp[i] != '\0' && i < N * N) {
        if (temp[i] == '.') {
          num = 0;
        } else {
          if (!char_is_number(temp[i])) {
            return ERR;
          }
          num = char_to_num(temp[i]);
        }
        sudoku_set_number(solution, i / N, i % N, num);
        i++;
      }

      puzzle_index++;
    }
    fclose(file);
    return SUCCESS;
  }
  fclose(file);
  printf("Could not read file \n");
  return ERR;
}

uint8_t sudoku_compare_grids(sudoku_t board, sudoku_t solution) {
  for (uint8_t row = 0; row < N; row++) {
    for (uint8_t col = 0; col < N; col++) {
      if (sudoku_get_number(board, row, col) !=
          sudoku_get_number(solution, row, col)) {
        return ERR;
      }
    }
  }
  return SUCCESS;
}

#define type int

uint8_t read_sudoku(const char *filename, sudoku_t sudoku) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Could not open file %s\n", filename);
    return ERR_FILE;
  }
  char temp[2] = "\0\0";
  type inserted = 81;
  type max_col = N;
  for (type line_number = 0; line_number < N;) {
    for (type col_number = 0; col_number < max_col;) {
      if (temp[0] == '\0') {
        if (fgets(temp, 2, file) == NULL) {
          fclose(file);
          return ERR; // error or EOF
        }
      }
      if (char_is_number(temp[0])) {
        sudoku_set_number(sudoku, line_number, col_number++,
                          char_to_num(temp[0]));
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
        return ERR;
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
    if (temp[0] == '\n' || !char_is_number(temp[0])) {
      temp[0] = '\0';
    }
    max_col = N;
  }
  fclose(file);
  return SUCCESS;
}

uint8_t verifySudoku(sudoku_t board) {
  uint8_t row, col;
  if (sudoku_is_solved(board, &row, &col) == SUCCESS) {
    return SUCCESS;
  }
  return ERR;
}

uint8_t sudoku_get_number(sudoku_t sudoku, uint8_t row, uint8_t col) {
  return sudoku[row][col];
}

uint8_t sudoku_set_number(sudoku_t sudoku, uint8_t row, uint8_t col,
                          uint8_t value) {
  return sudoku[row][col] = value;
}

void sudoku_empty_grid(sudoku_t sudoku) {
  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      sudoku_set_number(sudoku, row, col, 0);
    }
  }
}

int sudoku_is_valid_solved(sudoku_t sudoku) {
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
      for (int i = 1; i <= 9; i++)
        seen[i] = 0;
      for (uint8_t r = 0; r < 3; r++) {
        for (uint8_t c = 0; c < 3; c++) {
          uint8_t num =
              sudoku_get_number(sudoku, boxRow * 3 + r, boxCol * 3 + c);
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

int sudoku_from_line(sudoku_t sudoku, const char *line) {
  if (line == NULL) {
    return ERR;
  }
  size_t pos = 0;

  for (uint8_t row = 0; row < 9; row++) {
    for (uint8_t col = 0; col < 9; col++) {
      char ch = line[pos++];
      uint8_t value = 0;

      if (ch >= '1' && ch <= '9')
        value = (uint8_t)(ch - '0');
      else if (ch == '.')
        value = 0;
      else
        return ERR;

      sudoku_set_number(sudoku, row, col, value);
    }
  }
  return SUCCESS;
}