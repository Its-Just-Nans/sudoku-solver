 #include <stdio.h>

int verificateurFini();
int trueVerifier();
int charTOint(char aConvertir[1]);
char intTOchar(int aConvertir);
int lectureFichier();
int checkChiffre2(int quelChiffre, int ligne, int colonne);
int mmChiffreCase2(int aConvertir, int  ligne, int colonne,char test[9][9]);
int mmChiffreVerticale2(int quelChiffre,int  ligne,int  colonne,char test[9][9]);
int mmChiffreHorizontal2(int quelChiffre,int  ligne,int  colonne,char test[9][9]);
int a = 0;
int b = 0;
int e = 0;
int l = 0;
int m = 0;
int t = 0;
int r = 0;
int f = 0;
int x = 0;
int w = 0;
int afficheurLog = 0;
char globalSudoku[9][9];
int afficheurSudoku();


int main()
{
	printf("======================Prgm-CheSu======================\n");
	lectureFichier();
	int trueVerif = 0;
	int verificateur = 0;

	afficheurSudoku();
	trueVerif = trueVerifier();
	verificateur = verificateurFini();
	if(trueVerif == 0 && verificateur == 1)
	{
		printf("\n");
		printf("Le sudoku est juste\n");
		printf("\n");
	}
	else
	{
		printf("\n");
		printf("Le sudoku est faux\n");
		printf("\n");
	}
	printf("======================End-CheSu=======================\n");
	return 0;
}

int lectureFichier()
{
	char variablePoubelle[1];
	FILE *sudoku;
	sudoku = fopen("sudokuResolu.txt", "r");
	if(sudoku != NULL)
	{
	    for(r=0; r<9; r++)
        {
            for(f=0; f<9; f++)
            {
                fscanf(sudoku, "%c", &globalSudoku[r][f]);
                fscanf(sudoku, "%c", &variablePoubelle[0]);
            }
            fscanf(sudoku, "\n", &variablePoubelle[0]);
		}
	}
	else
	{
		printf("Erreur lecture fichier");
	}
	fclose(sudoku);
	return 0;
}


int afficheurSudoku()
{
    printf("\nThe sudoku :\n");
	for(x=0; x<9; x++)
	{
		for(w=0; w<9; w++)
		{
			printf("%c", globalSudoku[x][w]);
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



int verificateurFini()
{
    for(m=0; m<9; m++)
    {
        for(l=0; l<9; l++)
        {
            if(globalSudoku[m][l] == '0')
            {
		printf("Le sudoku contient un ou plusieurs 0\n");
                return 0;
            }

        }
    }
    return 1;
}

int trueVerifier()
{
    char charChiffreActual[1];
    charChiffreActual[0] = '0';
    int chiffreActual = 0;
    int checker = 0;
    for(e=0; e<9; e++)
    {
        for(t=0; t<9; t++)
        {
            charChiffreActual[0] = globalSudoku[e][t];
            chiffreActual = charTOint(charChiffreActual);
            if(chiffreActual != 0)
            {
                checker = checkChiffre2(chiffreActual, e, t);
                if(checker == 0)
                {
                    if(afficheurLog == 1)                                                                                                                                         // a changer en 1
                    {
                        //printf("Verificateur ok pour [%d][%d]\n", e, t);
                    }
                }
                else
                {
                    if(afficheurLog == 1)                                                                                                                                       // a changer en 1
                    {
                        printf("Verificateur PAS ok pour [%d][%d]\n", e, t);
                    }
                    return 1;
                }
            }
        }
    }
    if(afficheurLog == 1)                                                                                                                                       // a changer en 1
    {
        printf("Le sudoku est correct\n");
    }
    return 0;
}

int charTOint(char aConvertir[1])
{
    if(aConvertir[0] == 48)
    {
        return 0;
    }
    if(aConvertir[0] == 49)
    {
        return 1;
    }
    if(aConvertir[0] == 50)
    {
        return 2;
    }
    if(aConvertir[0] == 51)
    {
        return 3;
    }
    if(aConvertir[0] == 52)
    {
        return 4;
    }
    if(aConvertir[0] == 53)
    {
        return 5;
    }
    if(aConvertir[0] == 54)
    {
        return 6;
    }
    if(aConvertir[0] == 55)
    {
        return 7;
    }
    if(aConvertir[0] == 56)
    {
        return 8;
    }
    if(aConvertir[0] == 57)
    {
        return 9;
    }

}


char intTOchar(int aConvertir)
{
    if(aConvertir == 0)
    {
        return 48;
    }
    if(aConvertir == 1)
    {
        return 49;
    }
    if(aConvertir == 2)
    {
        return 50;
    }
    if(aConvertir == 3)
    {
        return 51;
    }
    if(aConvertir == 4)
    {
        return 52;
    }
    if(aConvertir == 5)
    {
        return 53;
    }
    if(aConvertir == 6)
    {
        return 54;
    }
    if(aConvertir == 7)
    {
        return 55;
    }
    if(aConvertir == 8)
    {
        return 56;
    }
    if(aConvertir == 9)
    {
        return 57;
    }

}





int checkChiffre2(int quelChiffre, int ligne, int colonne)
{
    int testeur1 = 0, testeur2 = 0, testeur3 = 0;
    testeur1 = mmChiffreCase2(quelChiffre, ligne, colonne, globalSudoku);
    testeur2 = mmChiffreHorizontal2(quelChiffre, ligne, colonne, globalSudoku);
    testeur3 = mmChiffreVerticale2(quelChiffre, ligne, colonne, globalSudoku);
    if(testeur1 == 0 && testeur2 == 0 && testeur3 == 0)
    {

        return 0;
    }
    else
    {
        printf("testeur1 = %d, testeur2 = %d, testeur3 = %d\n", testeur1, testeur2, testeur3);
        return 1;
    }
}



int mmChiffreHorizontal2(int aConvertir, int ligne, int colonne, char test[9][9])
{
    char quelChiffre[1];
    quelChiffre[0] = intTOchar(aConvertir);
	int compteurMmChiffre=0;
	for(a = 0; a<9; a++)
	{
			if(quelChiffre[0] == test[a][colonne])
			{
				compteurMmChiffre++;
			}
	}
	if(compteurMmChiffre == 0)
	{
		return 1;
	}
	if(compteurMmChiffre == 1)
	{
		return 0;
	}
	if(compteurMmChiffre > 1)
	{
		return 1;
	}
}

int mmChiffreVerticale2(int aConvertir, int ligne, int colonne, char test[9][9])
{
    char quelChiffre[1];
    quelChiffre[0] = intTOchar(aConvertir);
	int compteurMmChiffre=0;
	//printf("%d, %d, %d\n",aConvertir, ligne, colonne);
	for(b = 0; b<9; b++)
	{
		if(quelChiffre[0] == test[ligne][b])
		{
		    //afficheurSudoku();
		    //printf("LOL %c %d %d\n", test[ligne][b], ligne, b);
			compteurMmChiffre++;
		}
	}

	if(compteurMmChiffre == 0)
	{
		return 1;
	}
	if(compteurMmChiffre == 1)
	{
		return 0;
	}
	if(compteurMmChiffre > 1)
	{
		return 1;
	}
}








int mmChiffreCase2(int aConvertir, int  ligne, int colonne,char test[9][9])
{
    int compteur = 0;
    char quelChiffre[1];
    quelChiffre[0] = intTOchar(aConvertir);
    if(ligne>=0 && ligne <=2 && colonne>=0 && colonne <=2)
    {
        if(quelChiffre[0]==test[0][0] || quelChiffre[0]==test[0][1] || quelChiffre[0]==test[0][2] || quelChiffre[0]==test[1][0] || quelChiffre[0]==test[1][1] || quelChiffre[0]==test[1][2] || quelChiffre[0]==test[2][0] || quelChiffre[0]==test[2][1] || quelChiffre[0]==test[2][2])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=0 && ligne <=2 && colonne>=3 && colonne <=5)
    {
        if(quelChiffre[0]==test[0][3] || quelChiffre[0]==test[0][4] || quelChiffre[0]==test[0][5] || quelChiffre[0]==test[1][3] || quelChiffre[0]==test[1][4] || quelChiffre[0]==test[1][5] || quelChiffre[0]==test[2][3] || quelChiffre[0]==test[2][4] || quelChiffre[0]==test[2][5])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=0 && ligne <=2 && colonne>=6 && colonne <=8)
    {
        if(quelChiffre[0]==test[0][6] || quelChiffre[0]==test[0][7] || quelChiffre[0]==test[0][8] || quelChiffre[0]==test[1][6] || quelChiffre[0]==test[1][7] || quelChiffre[0]==test[1][8] || quelChiffre[0]==test[2][6] || quelChiffre[0]==test[2][7] || quelChiffre[0]==test[2][8])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=3 && ligne <=5 && colonne>=0 && colonne <=2)
    {
        if(quelChiffre[0]==test[3][0] || quelChiffre[0]==test[3][1] || quelChiffre[0]==test[3][2] || quelChiffre[0]==test[4][0] || quelChiffre[0]==test[4][1] || quelChiffre[0]==test[4][2] || quelChiffre[0]==test[5][0] || quelChiffre[0]==test[5][1] || quelChiffre[0]==test[5][2])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=3 && ligne <=5 && colonne>=3 && colonne <=5)
    {
        if(quelChiffre[0]==test[3][3] || quelChiffre[0]==test[3][4] || quelChiffre[0]==test[3][5] || quelChiffre[0]==test[4][3] || quelChiffre[0]==test[4][4] || quelChiffre[0]==test[4][5] || quelChiffre[0]==test[5][3] || quelChiffre[0]==test[5][4] || quelChiffre[0]==test[5][5])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=3 && ligne <=5 && colonne>=6 && colonne <=8)
    {
        if(quelChiffre[0]==test[3][6] || quelChiffre[0]==test[3][7] || quelChiffre[0]==test[3][8] || quelChiffre[0]==test[4][6] || quelChiffre[0]==test[4][7] || quelChiffre[0]==test[4][8] || quelChiffre[0]==test[5][6] || quelChiffre[0]==test[5][7] || quelChiffre[0]==test[5][8])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=6 && ligne <=8 && colonne>=0 && colonne <=2)
    {
        if(quelChiffre[0]==test[6][0] || quelChiffre[0]==test[6][1] || quelChiffre[0]==test[6][2] || quelChiffre[0]==test[7][0] || quelChiffre[0]==test[7][1] || quelChiffre[0]==test[7][2] || quelChiffre[0]==test[8][0] || quelChiffre[0]==test[8][1] || quelChiffre[0]==test[8][2])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=6 && ligne <=8 && colonne>=3 && colonne <=5)
    {
        if(quelChiffre[0]==test[6][3] || quelChiffre[0]==test[6][4] || quelChiffre[0]==test[6][5] || quelChiffre[0]==test[7][3] || quelChiffre[0]==test[7][4] || quelChiffre[0]==test[7][5] || quelChiffre[0]==test[8][3] || quelChiffre[0]==test[8][4] || quelChiffre[0]==test[8][5])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(ligne>=6 && ligne <=8 && colonne>=6 && colonne <=8)
    {
        if(quelChiffre[0]==test[6][6] || quelChiffre[0]==test[6][7] || quelChiffre[0]==test[6][8] || quelChiffre[0]==test[7][6] || quelChiffre[0]==test[7][7] || quelChiffre[0]==test[7][8] || quelChiffre[0]==test[8][6] || quelChiffre[0]==test[8][7] || quelChiffre[0]==test[8][8])
        {
            compteur++;
        }
        else
        {
            return 0;
        }
    }
    if(compteur == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
