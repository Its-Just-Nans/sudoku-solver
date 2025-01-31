#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#ifndef VERBOSE
#define printf(...) ;
#else

void printByte2(uint8_t *byte)
{
    for (uint8_t count = 0; count < 8; count++)
    {
        uint8_t temp = (*byte) << (count);
        printf("%d ", temp >> 7);
    }
    printf("\n");
}

void printByte(uint16_t *byte)
{
    for (uint8_t count = 0; count < 16; count++)
    {
        uint16_t temp = (*byte) << (count);
        printf("%d ", temp >> 15);
    }
    printf("\n");
}

#endif

uint8_t getSmallNumber(uint16_t *byte, uint8_t number)
{
    uint16_t temp = (*byte) << (number - 1);
    return temp >> 15;
}

void setSmallNumber(uint16_t *byte, uint8_t number, uint8_t state)
{
    uint16_t numberOfCase = (*byte) << 12;
    numberOfCase = numberOfCase >> 12;   // we save the number of the case
    uint16_t smallNumber = (*byte) >> 7; // we get the part where numbers are
    // printByte(&smallNumber);printf(" => smallNumber\n");
    uint16_t firstPart = smallNumber >> (10 - number);
    uint16_t lastPart = smallNumber << (7 + number);
    lastPart = lastPart >> (7 + number);
    // printByte(&firstPart);printf(" => firstPart\n");
    // printByte(&lastPart);
    // printf(" => lastPart\n");
    firstPart = firstPart << 1;
    // printByte(&firstPart);printf(" => firstPart after shifting\n");
    firstPart = firstPart + state;
    // printByte(&firstPart);printf(" => firstPart after state\n");
    smallNumber = firstPart;
    smallNumber = smallNumber << (9 - number);
    smallNumber = smallNumber + lastPart;
    // printByte(&smallNumber);printf(" => smallNumber normal ok\n");
    (*byte) = smallNumber << 7;
    (*byte) = (*byte) + numberOfCase;
    // printByte(byte);printf(" => byte\n\n");
}

void setNumber(uint16_t *byte, uint8_t number)
{
    (*byte) = (*byte) >> 4;
    (*byte) = (*byte) << 4;     // remove the old number
    (*byte) = (*byte) + number; // replace by new number
}

uint8_t getNumber(uint16_t *byte)
{
    uint16_t temp = (*byte) << 12;
    temp = temp >> 12;
    return temp; // it is a uint16_t but it is casted to a uint8_t because we return a uint8_t
}

uint8_t getSmallNumber(uint16_t *byte, uint8_t number)
{
    uint16_t temp = (*byte) << (number - 1);
    return temp >> 15;
}

void printSmallNumber(uint16_t sudoku[9][9], uint8_t *col, uint8_t *row, uint8_t *num)
{
#ifdef VERBOSE
    uint8_t temp = getSmallNumber(&sudoku[*col][*row], num);
    printf("%hhd", temp);
#endif
}
void printNumber(uint16_t sudoku[9][9], uint8_t *col, uint8_t *row)
{
#ifdef VERBOSE
    uint8_t temp = getNumber(&sudoku[*col][*row]);
    printf("%hhd", temp);
#endif
}

void readFile(uint16_t sudoku[9][9], char const *nameOfFile, char const *vSeparator, char const *hSeparator)
{
    char trash;
    FILE *FileSudoku;
    uint8_t temp;
    FileSudoku = fopen(nameOfFile, "r");
    if (FileSudoku != NULL)
    {
        for (uint8_t count = 0; count < 9; count++)
        {
            for (uint8_t f = 0; f < 9; f++)
            {
                fgets(&temp, 1, FileSudoku);
                setNumber(&sudoku[count][f], temp);
                if (isNumber(&sudoku[count][f]))
                {
#ifdef DEBUG
                    printf("      [%d][%d] = %d\n", count, f, getNumber(&sudoku[count][f]));
#endif
                    setAllSmallNumberToZero(&sudoku[count][f]);
                }
                if (f != 8)
                {
                    fgets(&temp, 1, FileSudoku);
                }
                if (vSeparator != NULL && (f == 2 || f == 5))
                {
                    fgets(&temp, 1, FileSudoku);
                    fgets(&temp, 1, FileSudoku);
                }
            }
            fgets(&temp, 1, FileSudoku); // \n
            if (hSeparator != NULL && (count == 2 || count == 5))
            {
                for (uint8_t f = 0; f < 21; f++)
                {
                    fgets(&temp, 1, FileSudoku); // hSeparator
                }
                fgets(&temp, 1, FileSudoku); // \n
            }
        }
        fclose(FileSudoku);
    }
    else
    {
        printf("Error during file opening\n");
    }
}

void getRowFROMFILE(char const *nameOfFile, char const *verticalSeparator, char const *horizontalSeparator, uint8_t rowNumber, uint8_t *buffer)
{
    char trash;
    FILE *FileSudoku;
    uint8_t temp;
    FileSudoku = fopen(nameOfFile, "r");
    if (FileSudoku != NULL)
    {
        for (uint8_t count = 0; count < 9; count++)
        {
            for (uint8_t f = 0; f < 9; f++)
            {
                fscanf(FileSudoku, "%hhd", &temp);
                if (count == (rowNumber - 1))
                {
                    buffer[f] = temp;
                }
                if (f != 8)
                {
                    fscanf(FileSudoku, " ");
                }
                if (verticalSeparator != NULL && (f == 2 || f == 5))
                {
                    fscanf(FileSudoku, verticalSeparator, &trash);
                    fscanf(FileSudoku, " ");
                }
            }
            fscanf(FileSudoku, "\n");
            if (horizontalSeparator != NULL && (count == 2 || count == 5))
            {
                for (uint8_t f = 0; f < 21; f++)
                {
                    fscanf(FileSudoku, horizontalSeparator, &trash);
                }
                fscanf(FileSudoku, "\n");
            }
        }
        fclose(FileSudoku);
    }
    else
    {
        printf("Error during file opening\n");
    }
}

void getColumnFROMFILE(char const *nameOfFile, char const *verticalSeparator, char const *horizontalSeparator, uint8_t columnNumber, uint8_t *buffer)
{
    char trash;
    FILE *FileSudoku;
    uint8_t temp;
    FileSudoku = fopen(nameOfFile, "r");
    if (FileSudoku != NULL)
    {
        for (uint8_t count = 0; count < 9; count++)
        {
            for (uint8_t f = 0; f < 9; f++)
            {
                fscanf(FileSudoku, "%hhd", &temp);
                if (f == (columnNumber - 1))
                {
                    buffer[count] = temp;
                }
                if (f != 8)
                {
                    fscanf(FileSudoku, " ");
                }
                if (verticalSeparator != NULL && (f == 2 || f == 5))
                {
                    fscanf(FileSudoku, verticalSeparator, &trash);
                    fscanf(FileSudoku, " ");
                }
            }
            fscanf(FileSudoku, "\n");
            if (horizontalSeparator != NULL && (count == 2 || count == 5))
            {
                for (uint8_t f = 0; f < 21; f++)
                {
                    fscanf(FileSudoku, horizontalSeparator, &trash);
                }
                fscanf(FileSudoku, "\n");
            }
        }
        fclose(FileSudoku);
    }
    else
    {
        printf("Error during file opening\n");
    }
}

uint8_t checkFile(char *nameOfFile)
{
    FILE *sudokuFile;
    sudokuFile = fopen(nameOfFile, "r");
    if (sudokuFile != NULL)
    {
        fclose(sudokuFile);
        return 0;
    }
    else
    {
        perror("Error");
        printf("fopen failed, errno = %d\n", errno);
        printf("Error during file opening\n");
        return 1;
    }
}

void getSquareFROMFILE(char const *nameOfFile, char const *verticalSeparator, char const *horizontalSeparator, uint8_t squareNumber, uint8_t *buffer)
{
    char trash;
    FILE *FileSudoku;
    uint8_t temp;
    uint8_t countSquare = 0;
    FileSudoku = fopen(nameOfFile, "r");
    for (uint8_t count = 0; count < 9; count++)
    {
        for (uint8_t f = 0; f < 9; f++)
        {
            if (squareNumber == 1 || squareNumber == 4 || squareNumber == 7)
            {
                fscanf(FileSudoku, "%hhd", &temp);
                if (f < 3)
                {
                    buffer[countSquare++] = temp;
                }
            }
            if (squareNumber == 2 || squareNumber == 5 || squareNumber == 8)
            {
                fscanf(FileSudoku, "%hhd", &temp);
                if (f >= 3 && f < 6)
                {
                    buffer[countSquare++] = temp;
                }
            }
            if (squareNumber == 3 || squareNumber == 6 || squareNumber == 9)
            {
                fscanf(FileSudoku, "%hhd", &temp);
                if (f >= 6)
                {
                    buffer[countSquare++] = temp;
                }
            }
            if (f != 8)
            {
                fscanf(FileSudoku, " ");
            }
            if (verticalSeparator != NULL && (f == 2 || f == 5))
            {
                fscanf(FileSudoku, verticalSeparator, &trash);
                fscanf(FileSudoku, " ");
            }
        }
        fscanf(FileSudoku, "\n");
        if (count == 2)
        {
            if (squareNumber == 1 || squareNumber == 2 || squareNumber == 3)
            {
                break;
            }
            else
            {
                countSquare = 0; // reset the value
            }
        }
        else if (count == 5)
        {
            if (squareNumber == 4 || squareNumber == 5 || squareNumber == 6)
            {
                break;
            }
            else
            {

                countSquare = 0; // reset the value
            }
        }
        if (horizontalSeparator != NULL && (count == 2 || count == 5))
        {
            for (uint8_t f = 0; f < 21; f++)
            {
                fscanf(FileSudoku, horizontalSeparator, &trash);
            }
            fscanf(FileSudoku, "\n");
        }
    }
    fclose(FileSudoku);
}

void afficheurSudoku(uint16_t sudoku[9][9][1], char const *vSeparator, char const *hSeparator)
{
    uint8_t temp;
    for (uint8_t counterL = 0; counterL < 9; counterL++)
    {
        for (uint8_t counterC = 0; counterC < 9; counterC++)
        {
            temp = getNumber(&sudoku[counterL][counterC][0]);
            printf("%hhd", temp);
            if (counterC != 8)
            {
                printf(" ");
            }
            if (vSeparator != NULL && (counterC == 2 || counterC == 5))
            {
                printf(vSeparator);
                printf(" ");
            }
        }
        printf("\n");
        if (hSeparator != NULL && (counterL == 2 || counterL == 5))
        {
            for (uint8_t f = 0; f < 21; f++)
            {
                printf(hSeparator);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void afficheurFullSudoku(uint16_t sudoku[9][9][1])
{
    uint8_t temp;
    for (uint8_t counterL = 0; counterL < 9; counterL++)
    {
        for (uint8_t counterC = 0; counterC < 9; counterC++)
        {
            printf("[%d][%d] = ", counterL, counterC);
            for (uint8_t countSmallNumber = 1; countSmallNumber < 10; countSmallNumber++)
            {
                temp = getSmallNumber(&sudoku[counterL][counterC][0], countSmallNumber);
                printf("%hhd ", temp);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void getColumn(uint16_t sudoku[9][9][1], uint8_t nbColumn, uint8_t *buffer)
{
    for (uint8_t count = 0; count < 9; count++)
    {
        buffer[count] = getNumber(&sudoku[count][(nbColumn - 1)][0]);
    }
}

void getRow(uint16_t sudoku[9][9][1], uint8_t nbRow, uint8_t *buffer)
{
    for (uint8_t count = 0; count < 9; count++)
    {
        buffer[count] = getNumber(&sudoku[(nbRow - 1)][count][0]);
    }
}

uint8_t isNumberInBuffer(uint8_t *buffer, uint8_t number)
{
    for (uint8_t count = 0; count < 9; count++)
    {
        if (buffer[count] == number)
        {
            return 1;
        }
    }
    return 0;
}

void setSmallNumberOfColumn(uint16_t sudoku[9][9], uint8_t numberOfColumn, uint8_t *buffer)
{
    getColumn(sudoku, numberOfColumn, buffer);
    for (uint8_t number = 1; number < 10; number++)
    {
        if (isNumberInBuffer(buffer, number))
        {
            for (uint8_t count = 0; count < 9; count++)
            {
                if (!isNumber(&sudoku[count][(numberOfColumn - 1)]))
                {
                    setSmallNumber(&sudoku[count][(numberOfColumn - 1)], number, 0);
                }
            }
        }
        // else
        // {
        //     for (uint8_t count = 0; count < 9; count++)
        //     {
        //         setSmallNumber(&sudoku[count][(numberOfColumn - 1)][0], number, 1);
        //     }
        // }
    }
}

void setSmallNumberOfRow(uint16_t sudoku[9][9][1], uint8_t numberOfRow, uint8_t *buffer)
{
    getRow(sudoku, numberOfRow, buffer);
    for (uint8_t number = 1; number < 10; number++)
    {
        if (isNumberInBuffer(buffer, number))
        {
            for (uint8_t count = 0; count < 9; count++)
            {
                if (!isNumber(&sudoku[(numberOfRow - 1)][count][0]))
                {
                    setSmallNumber(&sudoku[(numberOfRow - 1)][count][0], number, 0);
                }
            }
        }
    }
}

void getSquare(uint16_t sudoku[9][9][1], uint8_t nbSquare, uint8_t *buffer)
{
    uint8_t startLine = 0;
    if (nbSquare == 1 || nbSquare == 2 || nbSquare == 3)
    {
        startLine = 0;
        // it's default, so this test is useless
    }
    else if (nbSquare == 4 || nbSquare == 5 || nbSquare == 6)
    {
        startLine = 3;
    }
    else if (nbSquare == 7 || nbSquare == 8 || nbSquare == 9)
    {
        startLine = 6;
    }
    uint8_t startColumn = 0;
    if (nbSquare == 1 || nbSquare == 4 || nbSquare == 7)
    {
        startColumn = 0;
        // it's default, so this test is useless
    }
    else if (nbSquare == 2 || nbSquare == 5 || nbSquare == 8)
    {
        startColumn = 3;
    }
    else if (nbSquare == 3 || nbSquare == 6 || nbSquare == 9)
    {
        startColumn = 6;
    }
    for (uint8_t count = 0; count < 9; count++)
    {
        if (count == 0 || count == 3 || count == 6)
        {
            buffer[count] = getNumber(&sudoku[startLine][startColumn][0]);
        }
        else if (count == 1 || count == 4 || count == 7)
        {
            buffer[count] = getNumber(&sudoku[startLine][startColumn + 1][0]);
        }
        else if (count == 2 || count == 5 || count == 8)
        {
            buffer[count] = getNumber(&sudoku[startLine][startColumn + 2][0]);
            startLine++;
        }
    }
}

void setSmallNumberOfSquare(uint16_t sudoku[9][9], uint8_t nbSquare, uint8_t *buffer)
{
    getSquare(sudoku, nbSquare, buffer);
    uint8_t startLine = 0;
    if (nbSquare == 1 || nbSquare == 2 || nbSquare == 3)
    {
        startLine = 0;
        // it's default, so this test is useless
    }
    else if (nbSquare == 4 || nbSquare == 5 || nbSquare == 6)
    {
        startLine = 3;
    }
    else if (nbSquare == 7 || nbSquare == 8 || nbSquare == 9)
    {
        startLine = 6;
    }
    uint8_t startColumn = 0;
    if (nbSquare == 1 || nbSquare == 4 || nbSquare == 7)
    {
        startColumn = 0;
        // it's default, so this test is useless
    }
    else if (nbSquare == 2 || nbSquare == 5 || nbSquare == 8)
    {
        startColumn = 3;
    }
    else if (nbSquare == 3 || nbSquare == 6 || nbSquare == 9)
    {
        startColumn = 6;
    }
    for (uint8_t number = 1; number < 10; number++)
    {
        uint8_t startTemp = startLine;
        if (isNumberInBuffer(buffer, number))
        {
            for (uint8_t count = 0; count < 9; count++)
            {
                if (count == 0 || count == 3 || count == 6)
                {
                    if (!isNumber(&sudoku[startTemp][startColumn]))
                    {
                        setSmallNumber(&sudoku[startTemp][startColumn], number, 0);
                    }
                }
                else if (count == 1 || count == 4 || count == 7)
                {
                    if (!isNumber(&sudoku[startTemp][startColumn + 1]))
                    {
                        setSmallNumber(&sudoku[startTemp][startColumn + 1], number, 0);
                    }
                }
                else if (count == 2 || count == 5 || count == 8)
                {
                    if (!isNumber(&sudoku[startTemp][startColumn + 2]))
                    {
                        setSmallNumber(&sudoku[startTemp][startColumn + 2], number, 0);
                    }
                    startTemp++;
                }
            }
        }
    }
}

void printBuffer(uint8_t *buffer)
{
    for (uint8_t count = 0; count < 9; count++)
    {
        printf("%d ", buffer[count]);
    }
    printf("\n");
}
