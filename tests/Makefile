FILE_OUT=test.out

all: build run

debug: build-debug run-debug

build-debug:
	gcc -o $(FILE_OUT) -g test.c ../sudoku.c

run-debug:
	valgrind ./$(FILE_OUT)

build:
	gcc -o $(FILE_OUT) test.c ../sudoku.c
run:
	./$(FILE_OUT)
