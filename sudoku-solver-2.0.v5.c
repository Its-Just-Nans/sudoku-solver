#include <stdio.h>

struct Ssudoku
{
	char grilleSudoku[9][9][9];
};

void readFile(struct Ssudoku* Psudoku); //permet de remplir la structure avec le fichier sudoku.txt
void displaySudoku(struct Ssudoku* Psudoku); //permet d'afficher la structure (donc le sudoku)
void filler(struct Ssudoku* Psudoku, &rest); //permet de remplir le sudoku

int main(int argc, char *argv[])
{
	int log = 0;
	if(argc > 1)
	{
		if(argv[1][0] == '-' && argv[1][1] == 'l' )
		{
			log = 1;
			printf("Les logs sont activés\n");
		}
	}
	struct Ssudoku sudoku;
	readFile(&sudoku);
	displaySudoku(&sudoku);
	int prgrmStop = 0;
	int cmpt = 0;
	int checker = 0;
	int rest = 1;
	while(prgrmStop == 0)
	{
		miniCase(struct Ssudoku* Psudoku);	
		filler(struct Ssudoku* Psudoku, &rest);
		cmpt ++;
      		checker = verificateurFini();
		if(cmpt == rest || checker == 1)
		{
		    prgmStop = 1;
		}
	}
	return 0;
}


void readFile(struct Ssudoku* Psudoku)
{
	char trash[1];
	FILE *FileSudoku;
	FileSudoku = fopen("sudoku.txt", "r");
	if(FileSudoku != NULL)
	{
		for(int r=0; r<9; r++)
		{
			for(int f=0; f<9; f++)
			{
			        fscanf(FileSudoku, "%c", &(*Psudoku).grilleSudoku[r][f][0]);
			        fscanf(FileSudoku, "%c", &trash[0]);
			}
			fscanf(FileSudoku, "\n", &trash[0]);
		}
	}
	else
	{
		printf("Erreur lecture fichier");
	}
	fclose(FileSudoku);
}

void displaySudoku(struct Ssudoku* Psudoku)
{
    printf("\nThe sudoku :\n");
	for(int x=0; x<9; x++)
	{
		for(int w=0; w<9; w++)
		{
			printf("%c", (*Psudoku).grilleSudoku[x][w][0]);
			if(w==2 || w==5 || w==9)
            {
                printf("|");
            }
		}
		printf("\n");
		if(x==2 || x==5 || x==9)
            {
                printf("===========\n");
            }
    }
	printf("\n");
}

void filler(struct Ssudoku* Psudoku, &rest)
{
	int chiffreSeulOuiNonAConvertir = 0;
	int uniqueSousChiffreCaseOuiNonAConvertir = 0;
	char uniqueSousChiffreCaseOuiNon = '0';
	char uniqueSousChiffre = '0';
	char sousChiffre = '0';
	for(u=0; u<9; u++)
	{
		for(p=0; p<9; p++)
		{
			if(*(Psudoku).grilleSudoku[u][p][0] == '0')
			{
				sousChiffre = sousChiffreSeul(u, p);
				uniqueSousChiffre = uniqueSousChiffreCase(u, p);
				if(sousChiffre != '0')
				{
					globalSudoku[u][p][0] = uniqueSousChiffre;
				}
				if(afficheurLog == 0)
				{
					printf("1 Le chiffre %c a ete mis en [%d][%d]\n", sousChiffreSeulOuiNon[0], u, p);
					*rest ++;
				}

                }
                else
                {
                    if(uniqueSousChiffreCaseOuiNonAConvertir != 0)
                    {
                        uniqueSousChiffreCaseOuiNon[0] = intTOchar(uniqueSousChiffreCaseOuiNonAConvertir);
                        globalSudoku[u][p] = uniqueSousChiffreCaseOuiNon[0];
                        if(afficheurLog == 0)
                        {
                            printf("Le chiffre %c a ete mis en [%d][%d]\n", uniqueSousChiffreCaseOuiNon[0], u, p);
                        }
                    }
                }
                miniCase();

            }
        }
    }
}


char sousChiffreAlone(int ligne, int colonne)
{
	int compteurChiffre = 0;
	char chiffre = '0';
	for(f=0; f<9; f++)
	{
		if(globalGrandSudoku[ligne][colonne][f] != '0')
		{
			chiffre = globalGrandSudoku[ligne][colonne][f];
        		compteurChiffre ++;
		}
	}
	if(compteurChiffre == 1)
	{
		//printf("L'algo a trouve le chiffre donc il le return %d\n", chiffre);
		return chiffre;
	}
	else
	{
		//printf("Le chiffre n'est pas seul -> return 0\n", chiffre);
		return 0;
	}
}


int uniqueSousChiffreCase(int ligne, int colonne)
{
    int resultat = 0;
    if(ligne>=0 && ligne <=2 && colonne>=0 && colonne <=2)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 0, 0);
        return resultat;
    }
    if(ligne>=0 && ligne <=2 && colonne>=3 && colonne <=5)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 0, 3);
        return resultat;
    }
    if(ligne>=0 && ligne <=2 && colonne>=6 && colonne <=8)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 0, 6);
        return resultat;
    }
    if(ligne>=3 && ligne <=5 && colonne>=0 && colonne <=2)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 3, 0);
        return resultat;
    }
    if(ligne>=3 && ligne <=5 && colonne>=3 && colonne <=5)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 3, 3);
        return resultat;
    }
    if(ligne>=3 && ligne <=5 && colonne>=6 && colonne <=8)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 3, 6);
        return resultat;
    }
    if(ligne>=6 && ligne <=8 && colonne>=0 && colonne <=2)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 6, 0);
        return resultat;
    }
    if(ligne>=6 && ligne <=8 && colonne>=3 && colonne <=5)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 6, 3);
        return resultat;
    }
    if(ligne>=6 && ligne <=8 && colonne>=6 && colonne <=8)
    {
        resultat = fonctionSousChiffre(ligne, colonne, 6, 6);
        return resultat;
    }
}

int fonctionSousChiffre(int ligne, int colonne, int ligneCase, int colonneCase)
{
	int compteurChiffre = 0;
	int chiffre = 0;
	char aConvertir;
	char aideChar;
	for(int y=0; y<9; y++)
	{
		if((*Psudoku).grilleSudoku[ligne][colonne][y] != '0')
		{
			for(int n=ligneCase; n<(ligneCase+3); n++)
			{
				for(int i=colonneCase; i<(colonneCase+3); i++)
				{
					if(globalGrandSudoku[n][i][y] == globalGrandSudoku[ligne][colonne][y])
					{
						aideChar = globalGrandSudoku[ligne][colonne][y];
						chiffre = charTOint(aideChar);
						compteurChiffre ++;
					}
				}
			}
        	}
		if(compteurChiffre == 1)
		{
			//printf("L'algo a trouve le chiffre -> return %d\n", chiffre);
			return chiffre;
		}
	}
	return 0;
}
