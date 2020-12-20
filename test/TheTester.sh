#!/bin/sh

cd ~/Scripts/Sudoku
./GenSu-\(Generator\ for\ Sudoku\)/GenSu.sh
nbBoucle=$(echo $?)
echo "$nbBoucle"
for a in $(seq 1 $nbBoucle)
do
	./RenSU-\(Renamer\ Sudoku\)/RenSu.sh "$a"
	gcc ~/Scripts/Sudoku/ResSU-\(Resolver\ for\ Sudoku\)/VERSION-4.c -o ~/Scripts/Sudoku/ResSu.o
	./ResSu.o
	gcc ~/Scripts/Sudoku/CheSU-\(Checker\ for\ Sudoku\)/CheSu.c -o ~/Scripts/Sudoku/CheSu.o
	./CheSu.o
done