# sudoku-resolver

This is just a program for fun.
I know it's not optimized.

I think I am going to re-build it later/soon :)

### How to use
To use this program you need to create a text file with the sudoku (with 0 when there aren't number) named `sudoku1.txt`
like this :

```txt
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
This text file `sudoku1.txt` needs to be next to the program code.c
Then compile and execute code.c and the program will solve the sudoku on the screnn and in a file

### Documentation

This program use two method to solve the sudoku.

-The 1rst method is the logical one, sudoku have proprety to be solve.

But in a certain case, the sudoku can't be solve because you need to add a number.

- In this case, the 2nd method is used : it "bruteforce" the sudoku (in reality it just bruteforce at maximum 2 numbers, but we can change this number of course).


### Possible issues
1. Maybe you don't create correctly the `sudoku1.txt` file
2. Maybe you are trying to solve a sudoku with the brutforce method, and it'is need more numbers to brutforce.

You can change a value to activate the log !
