
#include "sudoku.h"

// Function to print the Sudoku board
void printBoard(int board[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}

// Function to check if it's safe to place a number at a given position
bool isSafe(int board[N][N], int row, int col, int num) {
  // Check if the number exists in the row
  for (int x = 0; x < N; x++) {
    if (board[row][x] == num) {
      return false;
    }
  }

  // Check if the number exists in the column
  for (int x = 0; x < N; x++) {
    if (board[x][col] == num) {
      return false;
    }
  }

  // Check if the number exists in the 3x3 subgrid
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i + startRow][j + startCol] == num) {
        return false;
      }
    }
  }

  return true;
}

bool checkIfSolved(int board[N][N], int *row, int *col) {
  for (*row = 0; *row < N; (*row)++) {
    for (*col = 0; *col < N; (*col)++) {
      if (board[*row][*col] == 0) {
        return false;
      }
    }
  }
  return true;
}

// Backtracking function to solve the Sudoku
bool solveSudoku(int board[N][N]) {
  int row, col;

  if (checkIfSolved(board, &row, &col)) {
    return true;
  }

  // Try numbers 1 to 9 for the empty cell
  for (int num = 1; num <= N; num++) {
    if (isSafe(board, row, col, num)) {
      board[row][col] = num;

      // Recursively attempt to solve with the current number
      if (solveSudoku(board)) {
        return true;
      }

      // If placing num doesn't lead to a solution, backtrack
      board[row][col] = 0;
    }
  }

  return false;
}
void get_splitted(char *line, int idx, char *res) {
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

int readSudokusFromCSV(FILE *restrict file, int board[N][N], int numPuzzles,
                       int solution[N][N]) {

  char line[1024];
  char temp[82];
  int puzzleIndex = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (puzzleIndex >= numPuzzles) {
      break;
    }

    // Read the line (excluding the ID) and parse the puzzle
    int num;
    int i = 0;
    // Skip the ID (first token)
    get_splitted(line, 1, temp);

    // Read puzzle into the 2D array
    while (temp[i] != '\0' && i < N * N) {
      if (temp[i] == '.') {
        num = 0;
      } else {
        num = temp[i] - '0';
      }
      board[i / N][i % N] = num;
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
          num = temp[i] - '0';
        }
        solution[i / N][i % N] = num;
        i++;
      }

      puzzleIndex++;
    }

    return 0;
  }
  printf("Could not read file \n");
  return -1;
}

int checkSudoku(int board[N][N], int solution[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j] != solution[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}