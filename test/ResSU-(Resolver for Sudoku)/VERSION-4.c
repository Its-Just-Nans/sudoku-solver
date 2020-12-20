#include <stdio.h>

/*

HELP

This program is a creation of Nans (one of his first programs)

To used this program you need to create a text file with the sudoku (with 0 when there aren't number) named sudoku.txt

To active log put the variable "afficheurLog" to 1

The function "afficheurGlobalGrandSudoku" is used to see the number possibilities in each box of the sudoku

The function "lectureValeurInterne" is used if you want to enter numbers of the sudoku directly in the program

The function "ecritureFichierBrut" is used if you want to write the final sudoku in the file sudokuResolu.txt without design

*/

char globalSudoku[9][9];
char globalGrandSudoku[9][9][9];
int mmChiffreCase(int aConvertir, int  ligne, int colonne,char test[9][9]);
int mmChiffreHorizontal(int aConvertir, int colonne, int ligne, char test[9][9]);
int mmChiffreVerticale(int aConvertir, int colonne, int ligne, char test[9][9]);
int checkChiffrePossible(int quelChiffre, int ligne, int colonne);
int afficheurGlobalGrandSudoku();
char intTOchar(int aConvertir);
int lectureValeurInterne();
int lectureFichier();
int miniCase();
int remplissageSudoku();
int sousChiffreSeul(int ligne, int colonne);
int uniqueSousChiffreCase(int ligne, int colonne);
int charTOint(char aConvertir[1]);
int afficheurSudoku();
int fonctionSousChiffre(int ligne, int colonne, int ligneCase, int colonneCase);
int verificateurFini();
int ecritureFichierClean();
int ecritureFichierBrut();
int saveFichier();
int prgmAvance(int valeur);
int prgmDansPrgm();
int loadSave();
int trueVerifier();
int afficheurLog = 0;
//intinalizing for the loop (not in one line because of nothing
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int m = 0;
int n = 0;
int o = 0;
int p = 0;
int q = 0;
int r = 0;
int s = 0;
int t = 0;
int u = 0;
int v = 0;
int w = 0;
int x = 0;
int y = 0;
int z = 0;

int aa = 0;
int ab = 0;
int ac = 0;
int ad = 0;
int ae = 0;
int af = 0;
int ag = 0;

int PrgmPartie2();

int checkChiffre2(int quelChiffre, int ligne, int colonne);
int mmChiffreCase2(int aConvertir, int  ligne, int colonne,char test[9][9]);
int mmChiffreVerticale2(int quelChiffre,int  ligne,int  colonne,char test[9][9]);
int mmChiffreHorizontal2(int quelChiffre,int  ligne,int  colonne,char test[9][9]);




int main()
{

    int trueVerif = 0;
    int verificateur = 0;
    int verificateur2 = 0;
    int boucleStop = 0;
    int compteurBoucle = 0;
    int variable = 0;
	lectureFichier();
	//lectureValeurInterne();
    afficheurSudoku();
    while(boucleStop == 0)
    {
        miniCase();
        remplissageSudoku();
        compteurBoucle ++;
        verificateur = verificateurFini();
        if(compteurBoucle == 90 || verificateur == 1)
        {
            boucleStop = 1;
        }
    }
    //afficheurSudoku();
    if(compteurBoucle == 90)
    {
        PrgmPartie2();

    }
    else
    {
        afficheurSudoku();
        ecritureFichierClean();
    }
    afficheurSudoku();
    ecritureFichierClean();
    //afficheurGlobalGrandSudoku();
    //printf("\n Le sudoku a ete resolu en %d boucles\n", compteurBoucle);
    ecritureFichierBrut();
	return 0;
}

int PrgmPartie2()
{
    int valeurPrgmAvance1 = 1;
    int valeurPrgmAvance2 = 1;
    int valeurPrgmAvance3 = 1;
    int valeurPrgmAvance4 = 1;
    int valeurPrgmAvance5 = 1;
    int valeurPrgmAvance6 = 1;
    int boucle = 0;
    int boucle1 = 0;
    int trueVerif = 0;
    int compteur = 0;
    int verificateur = 0;
        saveFichier();
        while(boucle1 == 0)
        {
            while(boucle == 0)
            {
                loadSave();
                //printf("La load a ete save\n\n");
                prgmAvance(valeurPrgmAvance1);
                miniCase();
                remplissageSudoku();
                trueVerif = trueVerifier();
                verificateur = verificateurFini();
                if(verificateur == 1)
                {
                    return 0;
                }
                if(trueVerif == 0)
                {
                    prgmAvance(valeurPrgmAvance2);
                    miniCase();
                    remplissageSudoku();
                    trueVerif = trueVerifier();
                    verificateur = verificateurFini();
                    if(verificateur == 1)
                    {
                        return 0;
                    }
                    if(trueVerif == 0)
                    {
                        prgmAvance(valeurPrgmAvance3);
                        miniCase();
                        remplissageSudoku();
                        trueVerif = trueVerifier();
                        verificateur = verificateurFini();
                        if(verificateur == 1)
                        {
                            return 0;
                        }
                        if(trueVerif == 0)
                        {
                            prgmAvance(valeurPrgmAvance4);
                            miniCase();
                            remplissageSudoku();
                            trueVerif = trueVerifier();
                            verificateur = verificateurFini();
                            if(verificateur == 1)
                            {
                                return 0;
                            }
                            if(trueVerif == 0)
                            {
                                prgmAvance(valeurPrgmAvance5);
                                miniCase();
                                remplissageSudoku();
                                trueVerif = trueVerifier();
                                verificateur = verificateurFini();
                                if(verificateur == 1)
                                {
                                    return 0;
                                }
                                if(trueVerif == 0)
                                {
                                    prgmAvance(valeurPrgmAvance6);
                                    miniCase();
                                    remplissageSudoku();
                                    trueVerif = trueVerifier();
                                    verificateur = verificateurFini();
                                    if(verificateur == 1)
                                    {
                                        return 0;
                                    }
                                    boucle = 1;
                                    compteur ++;
                                }
                                else
                                {
                                    loadSave();
                                    printf("La load a ete save\n\n");
                                    boucle = 1;
                                }
                                compteur ++;
                            }
                            else
                            {
                                loadSave();
                                printf("La load a ete save\n\n");
                                boucle = 1;
                            }
                        }
                        else
                        {
                            loadSave();
                            printf("La load a ete save\n\n");
                             boucle = 1;
                        }
                    }
                    else
                    {
                        loadSave();
                        printf("La load a ete save\n\n");
                        boucle = 1;
                    }
                }
                else
                {
                    loadSave();
                    printf("La load a ete save\n\n");
                    boucle = 1;
                }
            if(compteur == 400)
            {
                boucle1 = 1;
                boucle = 1;
            }

            }

            if(valeurPrgmAvance1 == 1)
            {
                valeurPrgmAvance1 = 2;
            }
            else
            {
                if(valeurPrgmAvance2 == 1)
                {
                    valeurPrgmAvance2 = 2;
                }
                else
                {
                    if(valeurPrgmAvance3 == 1)
                    {
                        valeurPrgmAvance3 == 2;
                    }
                    else
                    {
                        if(valeurPrgmAvance4 == 1)
                        {
                            valeurPrgmAvance4 == 2;
                        }
                        else
                        {
                            if(valeurPrgmAvance5 == 1)
                            {
                                valeurPrgmAvance5 == 2;
                            }
                            else
                            {
                                if(valeurPrgmAvance6 == 1)
                                {
                                    valeurPrgmAvance6 == 2;
                                }
                                else
                                {

                                }
                            }
                        }
                    }
                }
            }
            boucle = 0;

        }
    return 0;


        /*
        printf("ON EST LA GROS \n");
        saveFichier();
        prgmAvance(valeurPrgmAvance);
        while(verificateur2 == 0)
        {
            verificateur = verificateurFini();
            trueVerif = trueVerifier();
            prgmDansPrgm();
            if(trueVerif == 0)
            {
                printf("moi jui la gros\n");
                valeurPrgmAvance = 1;
                prgmAvance(valeurPrgmAvance);

            }
            else
            {
                loadSave();
                printf("LA sauvegarde a ete load\n");
                //afficheurSudoku();
                valeurPrgmAvance = 2;
                prgmAvance(valeurPrgmAvance);
            }
            printf("%d\n", verificateur);
            if(variable >= 100 && verificateur == 0)
            {
                loadSave();
                printf("LA sauvegarde a ete load\n");
                //afficheurSudoku();
                valeurPrgmAvance = 2;
                prgmAvance(valeurPrgmAvance);
            }
            variable ++;
            if( variable == 100)
            {
               verificateur2 = 1;
            }
        }*/
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

int prgmDansPrgm()
{
    int boucleStop = 0;
    int compteurBoucle = 0;
    int verificateur = 0;
    while(boucleStop == 0)
    {
        miniCase();
        remplissageSudoku();
        compteurBoucle ++;
        verificateur = verificateurFini();
        if(compteurBoucle == 90 || verificateur == 1)
        {
            boucleStop = 1;
        }
    }
}

int miniCase()
{
    int possibleOuiNon = 0;
    char valeurAide[1];
    valeurAide[0]='0';
    for(s=0; s<9; s++)
    {
        for(q=0; q<9; q++)
        {
            if(globalSudoku[s][q] == '0')
            {
                for(d=0; d<9; d++)
                {
                    possibleOuiNon = checkChiffrePossible((d+1), s, q);
                    valeurAide[0] = valeurAide[0]+1;

                    if (possibleOuiNon == 0)
                    {
                        globalGrandSudoku[s][q][d] = valeurAide[0];
                        //printf("globalGrandSudoku[%d][%d][%d] %c = %c\n", s, q, d, globalGrandSudoku[s][q][d], valeurAide[0]);
                    }
                    else
                    {
                        globalGrandSudoku[s][q][d] = '0';
                    }
                }
                valeurAide[0]='0';
            }
            else
            {
                for(e=0; e<9; e++)
                {
                    globalGrandSudoku[s][q][e] = globalSudoku[s][q];
                }
            }
        }
    }
}

int verificateurFini()
{
    for(m=0; m<9; m++)
    {
        for(l=0; l<9; l++)
        {
            if(globalSudoku[m][l] == '0')
            {
                return 0;
            }

        }
    }
    return 1;
}

int ecritureFichierClean()
{
	FILE *sudokuEcriture;
	sudokuEcriture = fopen("sudokuResolu.txt", "w");
	if(sudokuEcriture != NULL)
	{
	    for(t=0; t<9; t++)
        {
            for(z=0; z<9; z++)
            {
                fprintf(sudokuEcriture, "%c", globalSudoku[t][z]);
                if(z==2 || z==5 || z==9)
                {
                    fprintf(sudokuEcriture, "|");
                }
            }
            fprintf(sudokuEcriture, "\n");
            if(t==2 || t==5 || t==9)
            {
                fprintf(sudokuEcriture, "===========\n");
            }
		}
	}
	else
	{
		printf("Erreur ecriture fichier\n");
	}
	fclose(sudokuEcriture);
	return 0;
}

int ecritureFichierBrut()
{
	FILE *sudokuEcriture;
	sudokuEcriture = fopen("sudokuResolu.txt", "w");
	if(sudokuEcriture != NULL)
	{
	    for(t=0; t<9; t++)
        {
            for(g=0; g<9; g++)
            {
                fprintf(sudokuEcriture, "%c ", globalSudoku[t][g]);
            }
            fprintf(sudokuEcriture, "\n");
		}
	}
	else
	{
		printf("Erreur ecriture fichier\n");
	}
	fclose(sudokuEcriture);
	return 0;
}

int saveFichier()
{
	FILE *sudokuSave;
	sudokuSave = fopen("sudokuSave.txt", "w");
	if(sudokuSave != NULL)
	{
	    for(t=0; t<9; t++)
        {
            for(g=0; g<9; g++)
            {
                fprintf(sudokuSave, "%c ", globalSudoku[t][g]);
            }
            fprintf(sudokuSave, "\n");
		}
	}
	else
	{
		printf("Erreur ecriture fichier\n");
	}
	fclose(sudokuSave);
	return 0;
}

int prgmAvance(int valeur)
{
    int compteurMiniChiffre = 0;
    int compteurMiniChiffre2 = 0;
    for(u=0; u<9; u++)
    {
        for(p=0; p<9; p++)
        {
            if(globalSudoku[u][p] == '0')
            {
                for(f=0; f<9; f++)
                {
                    if(globalGrandSudoku[u][p][f] != '0')
                    {
                        compteurMiniChiffre ++;
                    }
                }
                if(compteurMiniChiffre == 2)
                {
                    for(z=0; z<9; z++)
                    {
                        if(globalGrandSudoku[u][p][z] != '0')
                        {


                            compteurMiniChiffre2++;
                            if(compteurMiniChiffre2 == 1)
                            {
                                if(valeur == 1)
                                {
                                    globalSudoku[u][p] = globalGrandSudoku[u][p][z];
                                    if(afficheurLog == 1)
                                    {
                                        printf("Le chiffre %c a ete mis en [%d][%d] (au hasard)\n", globalGrandSudoku[u][p][z], u, p);
                                    }
                                    return 0;
                                }
                                if(valeur == 2)
                                {
                                    compteurMiniChiffre2 = 0;
                                    valeur = 1;
                                }
                            }
                        }
                    }
                }
            }
            compteurMiniChiffre = 0;
        }
    }
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

int remplissageSudoku()
{
    int chiffreSeulOuiNonAConvertir = 0;
    int uniqueSousChiffreCaseOuiNonAConvertir = 0;
    char uniqueSousChiffreCaseOuiNon[1];
    uniqueSousChiffreCaseOuiNon[0];
    char sousChiffreSeulOuiNon[1];
    sousChiffreSeulOuiNon[0] = 0;
    for(u=0; u<9; u++)
    {
        for(p=0; p<9; p++)
        {
            if(globalSudoku[u][p] == '0')
            {

                chiffreSeulOuiNonAConvertir = sousChiffreSeul(u, p);
                uniqueSousChiffreCaseOuiNonAConvertir = uniqueSousChiffreCase(u, p);
                if(chiffreSeulOuiNonAConvertir != 0)
                {
                    sousChiffreSeulOuiNon[0] = intTOchar(chiffreSeulOuiNonAConvertir);
                    globalSudoku[u][p] = sousChiffreSeulOuiNon[0];
                    if(afficheurLog == 1)
                    {
                        printf("Le chiffre %c a ete mis en [%d][%d]\n", sousChiffreSeulOuiNon[0], u, p);
                    }

                }

                else
                {
                    if(uniqueSousChiffreCaseOuiNonAConvertir != 0)
                    {
                        uniqueSousChiffreCaseOuiNon[0] = intTOchar(uniqueSousChiffreCaseOuiNonAConvertir);
                        globalSudoku[u][p] = uniqueSousChiffreCaseOuiNon[0];
                        if(afficheurLog == 1)
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

int sousChiffreSeul(int ligne, int colonne)
{
	int compteurChiffre = 0;
	int chiffre = 0;
	char aConvertir[1];
	aConvertir[0];
    for(f*=0; f<9; f++)
    {
        if(globalGrandSudoku[ligne][colonne][f] != '0')
        {
        aConvertir[0] = globalGrandSudoku[ligne][colonne][f];
        chiffre = charTOint(aConvertir);
        compteurChiffre ++;

        }
	}
	if(compteurChiffre == 1)
	{
	    //printf("L'algo a trouve le chiffre -> return %d\n", chiffre);
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
	char aConvertir[1];
	aConvertir[0];
    char aideChar[1];
    aideChar[0];
    for(y=0; y<9; y++)
    {
        compteurChiffre = 0;
        if(globalGrandSudoku[ligne][colonne][y] != '0')
        {
            for(n=ligneCase; n<(ligneCase+3); n++)
            {
                for(i=colonneCase; i<(colonneCase+3); i++)
                {
                    if(globalGrandSudoku[n][i][y] == globalGrandSudoku[ligne][colonne][y])
                    {
                        aideChar[0] = globalGrandSudoku[ligne][colonne][y];
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

int afficheurGlobalGrandSudoku()
{
    for(j=0; j<9; j++)
    {
        for(h=0; h<9; h++)
        {
            printf("Les combinaisons pour la case[%d][%d]\n", j, h);
            for(v=0; v<9; v++)
            {
                printf("%c\n",globalGrandSudoku[j][h][v]);
            }
        }
    }
    return 0;
}

int checkChiffrePossible(int quelChiffre, int ligne, int colonne)
{
    int testeur1 = 0, testeur2 = 0, testeur3 = 0;
    testeur1 = mmChiffreCase(quelChiffre, ligne, colonne, globalSudoku);
    testeur2 = mmChiffreHorizontal(quelChiffre, ligne, colonne, globalSudoku);
    testeur3 = mmChiffreVerticale(quelChiffre, ligne, colonne, globalSudoku);
    if(testeur1 == 0 && testeur2 == 0 && testeur3 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
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

int mmChiffreCase(int aConvertir, int  ligne, int colonne,char test[9][9])
{
    char quelChiffre[1];
    quelChiffre[0] = intTOchar(aConvertir);
    if(ligne>=0 && ligne <=2 && colonne>=0 && colonne <=2)
    {
        if(quelChiffre[0]==test[0][0] || quelChiffre[0]==test[0][1] || quelChiffre[0]==test[0][2] || quelChiffre[0]==test[1][0] || quelChiffre[0]==test[1][1] || quelChiffre[0]==test[1][2] || quelChiffre[0]==test[2][0] || quelChiffre[0]==test[2][1] || quelChiffre[0]==test[2][2])
        {
            return 1;
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
            return 1;
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
            return 1;
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
            return 1;
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
            return 1;
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
            return 1;
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
            return 1;
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
            return 1;
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
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int lectureFichier()
{
	char variablePoubelle[1];
	FILE *sudoku;
	sudoku = fopen("sudoku1.txt", "r");
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

int loadSave()
{
	char variablePoubelle[1];
	FILE *sudoku;
	sudoku = fopen("sudokuSave.txt", "r");
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

int lectureValeurInterne()
{
	char tableau[9][9] = {{'1', '0', '7', '4', '0', '9', '8', '0', '5'}, {'0', '0', '9', '3', '0', '6', '1', '0', '0'}, {'0', '4', '0', '0', '0', '5', '0', '0', '3'}, {'7', '0', '0', '0', '5', '0', '2', '3', '0'}, {'0','5', '0', '0', '0', '0', '0', '8', '0'}, {'0', '6', '1', '0', '3', '0', '0', '0', '7'}, {'9', '0', '0', '7', '0', '0', '0', '1', '0'}, {'0', '0', '8', '5', '0', '3', '4', '0', '0'}, {'4', '0', '3', '2', '0', '1', '9', '0', '6'}};
	for(k=0; k<9; k++)
	{
		for(o=0; o<9; o++)
		{
            globalSudoku[k][o]= tableau[k][o];
		}
	}
}

int mmChiffreHorizontal(int aConvertir, int ligne, int colonne, char test[9][9])
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
		return 0;
	}
	if(compteurMmChiffre == 1)
	{
		return 1;
	}
	if(compteurMmChiffre > 1)
	{
		return 2;
	}
}

int mmChiffreVerticale(int aConvertir, int ligne, int colonne, char test[9][9])
{
    char quelChiffre[1];
    quelChiffre[0] = intTOchar(aConvertir);
	int compteurMmChiffre=0;
	for(b = 0; b<9; b++)
	{
		if(quelChiffre[0] == test[ligne][b])
		{
			compteurMmChiffre++;
		}
	}
	if(compteurMmChiffre == 0)
	{
		return 0;
	}
	if(compteurMmChiffre == 1)
	{
		return 1;
	}
	if(compteurMmChiffre > 1)
	{
		return 2;
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










