# sudoku-resolver
sudoku-resolver by Its-Just-Nans

### How to use
To use this program you need to create a text file with the sudoku (with 0 when there aren't number) named sudoku.txt
like this :

```
5 0 0 0 0 0 0 9 4
0 0 9 0 0 0 0 5 0
0 4 0 0 0 0 2 0 0
0 2 0 5 0 0 8 0 0
0 0 4 0 0 1 0 7 0
8 0 0 0 3 0 0 0 6
0 0 2 0 0 7 0 1 0
0 3 0 9 0 0 0 0 0
6 0 0 0 4 0 0 0 8
```
This text file sudoku.txt need to be next to the program code.c
Then compile and execute code.c and the program will resolve the sudoku

### Documentation

This program use two method to resolve the sudoku.
The 1rst methode is the logical one, a soduko have proprety to be solve.
Then in a certain case, the sudoku can't be resolve because you need to simulate a number.
The 2nd method is use in this case : it "brutforce" the sudoku
(in reality he just brutforce at maximum 2 numbers, but we can change this number of course).


### Possible issues
1. Maybe you don't create coreectly the sudoku.txt file
2. Maybe you are trying to solve a sudoku with the brutforce method, and it'is need more numbers to brutforce.

You can change a value to activate the log !
