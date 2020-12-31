#include <stdint.h>
#include <stdio.h>

/*
uint8_t leftByte(uint8_t* byte){
    return (*byte)>>4;
}

uint8_t rightByte(uint8_t* byte){
    uint8_t temp = (*byte)<<4;
    return temp>>4;
                                                        //((*byte)<<4)>>4; don't work (compiler optimization ?)
}

for(uint8_t c = 0; c <= 255; c++){
    printf("%d -> %d || %d\n", c, rightByte(&c), rightByte2(&c));
    if(c == 255){
        break;
    }
}
*/

void printByte2(uint8_t* byte){
    for(uint8_t count = 0; count < 8; count ++){
        uint8_t temp = (*byte)<<(count);
        printf("%d ", temp>>7);
    }
    printf("\n");
}

void printByte(uint16_t* byte){
    for(uint8_t count = 0; count < 16; count ++){
        uint16_t temp = (*byte)<<(count);
        printf("%d ", temp>>15);
    }
    printf("\n");
}

uint8_t getSmallNumber(uint16_t* byte, uint8_t number){
    uint16_t temp = (*byte)<<(number-1);
    return temp>>15;
}

void setSmallNumber(uint16_t* byte, uint8_t number, uint8_t state){
    uint16_t numberOfCase = (*byte)<<12;
    numberOfCase = numberOfCase>>12;                    // we save the number of the case
    uint16_t smallNumber = (*byte)>>7;                  // we get the part where numbers are
    // printByte(&smallNumber);printf(" => smallNumber\n");
    uint16_t firstPart = smallNumber>>(10-number);
    uint16_t lastPart = smallNumber<<(7+number);
    lastPart = lastPart>>(7+number);
    // printByte(&firstPart);printf(" => firstPart\n");
     printByte(&lastPart);printf(" => lastPart\n");
    firstPart = firstPart<<1;
    // printByte(&firstPart);printf(" => firstPart after shifting\n");
    firstPart = firstPart + state;
    // printByte(&firstPart);printf(" => firstPart after state\n");
    smallNumber = firstPart;
    smallNumber = smallNumber<<(9-number);
    smallNumber = smallNumber + lastPart;
    // printByte(&smallNumber);printf(" => smallNumber normal ok\n");
    (*byte) = smallNumber<<7;
    (*byte) = (*byte) + numberOfCase;
    // printByte(byte);printf(" => byte\n\n");
}

void setNumber(uint16_t* byte, uint8_t number){
    (*byte) = (*byte)>>4;
    (*byte) = (*byte)<<4;                                   //remove the old number
    (*byte) = (*byte) + number;                             //replace by new number
}

uint8_t getNumber(uint16_t* byte){
    uint16_t temp = (*byte)<<12;
    temp = temp>>12;
    return temp;                            //it is a uint16_t but it is casted to a uint8_t because we return a uint8_t
}

/*
printByte(&temp);printf(" => byte\n");
for(int c = 1; c<10; c++){
    setSmallNumber(&temp, c, 1);
    printByte(&temp);printf(" => temp after set small number %d 1\n", c);
    setNumber(&temp, c);
    printByte(&temp);printf(" => temp after set number\n");
    setSmallNumber(&temp, c, 0);
    printByte(&temp);printf(" => temp after set small number %d 0\n", c);
    printf("%d\n\n", getNumber(&temp));
}

printByte(&temp);printf(" => base\n");
for(int d = 1; d< 10; d++){
    printf("----------------------------------\n");
    printByte(&temp);printf(" => temp\n");
    printByte(&temp);printf(" => temp before set small\n");
    printf("%d => %d\n", d,getSmallNumber(&temp, d));
    setSmallNumber(&temp, d, 1);
    printByte(&temp);printf(" => temp after put 1\n");
    printf("%d => %d\n", d,getSmallNumber(&temp, d));
    setSmallNumber(&temp, d, 0);
    printByte(&temp);printf(" => temp after put 0\n");
    printf("%d => %d\n", d, getSmallNumber(&temp, d));
}
*/

void readFile(uint16_t sudoku[9][9][1], uint8_t* nameOfFile, char* vSeparator, char* hSeparator){
    char trash;
    FILE *FileSudoku;
    uint8_t temp;
	FileSudoku = fopen(nameOfFile, "r");
    if(FileSudoku != NULL){
        for(uint8_t count = 0; count < 9; count++){
			for(uint8_t f = 0; f < 9; f++){
                fscanf(FileSudoku, "%hu", &temp);
                setNumber(&sudoku[count][f][0], temp);
                if(f != 8){
                    fscanf(FileSudoku, " ", &trash);
                }
                if(vSeparator != "" && (f == 2 || f == 5)){
                    fscanf(FileSudoku, vSeparator, &trash);
                    fscanf(FileSudoku, " ", &trash);
                }
			}
			fscanf(FileSudoku, "\n", &trash);
            if(hSeparator != "" && (count == 2 || count == 5)){
                for(uint8_t f=0; f<21; f++){
			        fscanf(FileSudoku, hSeparator, &trash);
                }
                fscanf(FileSudoku, "\n", &trash);
            }
		}
    }else{
        printf("Error during file openning");
    }
    fclose(FileSudoku);
}

void afficheurSudoku(uint16_t sudoku[9][9][1], char* vSeparator, char* hSeparator){
    printf("The sudoku :\n");
    uint8_t temp;
	for(uint8_t counterL = 0; counterL < 9; counterL++){
		for(uint8_t counterC = 0; counterC < 9; counterC++){
            temp = getNumber(&sudoku[counterL][counterC][0]);
			printf("%d", temp);
            if(counterC != 8){
                printf(" ");
            }
			if(vSeparator != "" && (counterC == 2 || counterC == 5)){
                printf(vSeparator);
                printf(" ");
            }
		}
		printf("\n");
		if(hSeparator != "" && (counterL == 2 || counterL == 5)){
            for(uint8_t f=0; f<21; f++){
                printf(hSeparator);
            }
            printf("\n");
        }
    }
	printf("\n");
}





void getColumn(uint16_t sudoku[9][9][1], uint8_t* nameOfFile, uint8_t* option, uint8_t nbColumn, uint8_t* buffer){
    if((*option)){
        for(uint8_t count = 0; count < 9 ; count++){
            buffer[count] = getNumber(&sudoku[count][(nbColumn-1)][0]);
            printf("%d %d", buffer[count], getNumber(&sudoku[count][(nbColumn-1)][0]));
        }
        printf("\nsu printed\n");
    }else{
        printf("TODO readColumnFromFile\n");
    }
}

void getRow(uint16_t sudoku[9][9][1], uint8_t* nameOfFile, uint8_t* option, uint8_t nbRow, uint8_t* buffer){
    if((*option)){
        for(uint8_t count = 0; count < 9 ; count++){
            buffer[count] = getNumber(&sudoku[(nbRow-1)][count][0]);
        }
    }else{
        printf("TODO readRowFromFile\n");
    }
}