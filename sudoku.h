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
