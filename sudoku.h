#ifndef DEF_SUDOKU_FUNCTION

#define DEF_SUDOKU_FUNCTION

//uint8_t leftByte(uint8_t* byte);
//uint8_t rightByte(uint8_t* byte);
void readFile(uint16_t (*sudoku)[9][9][1], char const *nameOfFile, char const *vSeparator, char const *hSeparator);
void afficheurSudoku(uint16_t (*sudoku)[9][9][1], char *vSeparator, char *hSeparator);
void printByte(uint16_t *byte);
uint8_t getNumber(uint16_t *byte);
void setNumber(uint16_t *byte, uint8_t number);
uint8_t getSmallNumber(uint16_t *byte, uint8_t number);
void setSmallNumber(uint16_t *byte, uint8_t number, uint8_t state);
void getColumn(uint16_t (*sudoku)[9][9][1], uint8_t nbColumn, uint8_t *buffer);
void getRow(uint16_t (*sudoku)[9][9][1], uint8_t nbRow, uint8_t *buffer);
void getSquare(uint16_t (*sudoku)[9][9][1], uint8_t nbSquare, uint8_t *buffer);
uint8_t isNumberInBuffer(uint8_t *buffer, uint8_t number);
void setSmallNumberOfColumn(uint16_t (*sudoku)[9][9][1], uint8_t numberOfColumn, uint8_t *buffer);
void setSmallNumberOfRow(uint16_t (*sudoku)[9][9][1], uint8_t numberOfRow, uint8_t *buffer);
void printBuffer(uint8_t *buffer);
void getColumnFROMFILE(char const *nameOfFile, char const *verticalSeparator, char const *horizontalSeparator, uint8_t nbColumn, uint8_t *buffer); //TODO
void getRowFROMFILE(char const *nameOfFile, char const *verticalSeparator, char const *horizontalSeparator, uint8_t nbRow, uint8_t *buffer);       //TODO
void getSquareFROMFILE(char const *nameOfFile, char const *verticalSeparator, char const *horizontalSeparator, uint8_t nbSquare, uint8_t *buffer);
uint8_t checkFile(char const *nameOfFile); //TODO
#endif