#!/bin/sh

functionSUITE ()
{
	mkdir ~/Scripts/Sudoku/GenSu-\(Generator\ for\ Sudoku\)/tmp
	cd ~/Scripts/Sudoku/GenSu-\(Generator\ for\ Sudoku\)/tmp || exit
	nombre="$1"
	for i in $(seq 1 "$nombre")
	do
		echo ""
		echo "================Wget================"
		wget -P ./ https://www.e-sudoku.fr/grille-de-sudoku.php
		echo "==============End-Wget=============="
		echo ""
		helpValue=$(($i-1))
		if [ "$i" = 1 ]
		then
			grep -a 'Valeur ' grille-de-sudoku.php | sed -e 's:^.*\o351.* name="\(sudoku.*\)$:\1:g' | \
			sed -e 's:^sudoku\(\[[0123456789]\]\[[0123456789]\]\)" value="\([123456789]\).*:\1=\2:g' | \
			sort -n -t] > grilleBrut.txt 
		else
			grep -a 'Valeur ' grille-de-sudoku.php.$helpValue | sed -e 's:^.*\o351.* name="\(sudoku.*\)$:\1:g' | sed -e 's:^sudoku\(\[[0123456789]\]\[[0123456789]\]\)" value="\([123456789]\).*:\1=\2:g' | sort -n -t] > grilleBrut.txt 
		fi
		compteurL=1
		touch grilleClean"$i".txt
		for a in $(seq 0 '8')
		do
			valeurBoucle1=$a
			for b in $(seq 0 '8')
			do
				
				valeurUne=$(sed -n "$compteurL"p grilleBrut.txt | sed -e 's:\[\([0123456789]\)\].*:\1:g')
				valeurDeux=$(sed -n "$compteurL"p grilleBrut.txt | sed -e 's:\[[0123456789]\]\[\([0123456789]\)\].*:\1:g')
				value=$(sed -n "$compteurL"p grilleBrut.txt | sed -e 's:\[[0123456789]\]\[[0123456789]\]=\([123456789]\):\1:g')
				valeurBoucle2=$b
				if [ "$valeurBoucle1" = "$valeurUne" ] && [ "$valeurBoucle2" = "$valeurDeux" ]
				then
					echo "$value \c" >> grilleClean"$i".txt
					compteurL=$(($compteurL+1))
				else
					echo "0 \c" >> grilleClean"$i".txt
				fi
				
			done
			echo "\n\c" >> grilleClean"$i".txt
		done
	done
	mkdir page-php
	mv grille-de-sudoku.* ./page-php
}

echo ''
echo "==============Remove-file=============="
rm -R ~/Scripts/Sudoku/GenSu-\(Generator\ for\ Sudoku\)/tmp
echo 'Si pas de message, le fichier tmp a été supprimé'
echo "======================================="
echo ''


echo 'Combien de Sudoku, voulez-vous ? Veuillez saisir un chiffre entre 1 et 1 000'
read -r REPLY
bool=1
while [ "$bool" = '1' ]
do
	testValeur=$(echo "$REPLY" | grep '[1-9]')
	if [ -z "$testValeur" ]
	then
		echo "Veuillez re-donner un nombre"
		read -r REPLY
	else
		if [ "$testValeur" = '0' ] || [ "$testValeur" -ge '1000' ] || [ "$testValeur" -le '0' ]
		then
			echo "Veuillez re-donner un nombre"
			read -r REPLY
		else
			bool=2
		fi
	fi
done
nbSudoku=$REPLY

echo ""
echo "Voulez-vous vraiment $nbSudoku sudoku ?"
echo ""
echo 'Continue?[Yes/No]'
read -r reply2
if [ "$reply2" = "y" ] || [ "$reply2" = "yes" ] || [ "$reply2" = "Y" ] || [ "$reply2" = "Yes" ] || [ "$reply2" = "YES" ]
then
	echo "Let's go"
	echo ''
	functionSUITE "$nbSudoku"
	exit "$nbSudoku"
elif [ "$reply2" = "n" ] || [ "$reply2" = "no" ] || [ "$reply2" = "N" ] || [ "$reply2" = "No" ] || [ "$reply2" = "NO" ]
then
	echo 'Program Stop'
else
	echo 'Error'
fi
