#include <stdint.h>
#include <stdio.h>

uint8_t leftByte(uint8_t* byte){
    return (*byte)>>4;
}

uint8_t rightByte(uint8_t* byte){
    uint8_t temp = (*byte)<<4;
    return temp>>4;
    //((*byte)<<4)>>4; don't work
}

void readFile(uint8_t sudoku[9][9][9], uint8_t* nameOfFile, char* vSeparator, char* hSeparator){
    char trash;
    FILE *FileSudoku;
	FileSudoku = fopen(nameOfFile, "r");
    if(FileSudoku != NULL){
        for(int count = 0; count < 9; count++){
			for(int f = 0; f < 9; f++){
                fscanf(FileSudoku, "%c", &sudoku[count][f][1]);
                if(f != 8){
                    fscanf(FileSudoku, " ", &trash);
                }
                if(vSeparator != "" && (f == 2 || f == 5)){
                    fscanf(FileSudoku, vSeparator, &trash);
                    fscanf(FileSudoku, " ", &trash);
                }
			}
			fscanf(FileSudoku, "\n", trash);
            if(hSeparator != "" && (count == 2 || count == 5)){
                for(int f=0; f<21; f++){
			        fscanf(FileSudoku, hSeparator, &trash);
                }
                fscanf(FileSudoku, "\n", trash);
            }
		}
    }else{
        printf("Error during file openning");
    }
    fclose(FileSudoku);
}

void afficheurSudoku(uint8_t sudoku[9][9][9], char* vSeparator, char* hSeparator){
    printf("\nThe sudoku :\n");
	for(int counterL = 0; counterL < 9; counterL++){
		for(int counterC = 0; counterC < 9; counterC++){
			printf("%c", sudoku[counterL][counterC][1]);
            if(counterC != 8){
                printf(" ");
            }
			if(counterC == 2 || counterC == 5){
                printf(vSeparator);
                printf(" ");
            }
		}
		printf("\n");
		if(counterL == 2 || counterL == 5){
            for(int f=0; f<21; f++){
                printf(hSeparator);
            }
            printf("\n");
        }
    }
	printf("\n");
}