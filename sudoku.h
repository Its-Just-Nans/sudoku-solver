#ifndef DEF_SUDOKU_FUNCTION

#define DEF_SUDOKU_FUNCTION 

#include <stdio.h>
#include <stdint.h>

//uint8_t leftByte(uint8_t* byte);
//uint8_t rightByte(uint8_t* byte);
void readFile(uint16_t sudoku[9][9][1], uint8_t* nameOfFile, char* vSeparator, char* hSeparator);
void afficheurSudoku(uint16_t sudoku[9][9][1], char* vSeparator, char* hSeparator);
void printByte(uint16_t* byte);
uint8_t getNumber(uint16_t* byte);
void setNumber(uint16_t* byte, uint8_t number);
uint8_t getSmallNumber(uint16_t* byte, uint8_t number);
void setSmallNumber(uint16_t* byte, uint8_t number, uint8_t state);
void getColumn(uint16_t sudoku[9][9][1], uint8_t* nameOfFile, uint8_t* option, uint8_t nbColumn, uint8_t* buffer);
void getRow(uint16_t sudoku[9][9][1], uint8_t* nameOfFile, uint8_t* option, uint8_t nbRow, uint8_t* buffer);

#endif