FILE_OUT=test.out
CFLAGS_DEBUG= $(CFLAGS) -g -Wall -DDEBUG -DSUDOKU_VERBOSE -fstack-usage -pedantic -Wall -Wextra -Wcast-qual -Wcast-align -Wconversion  -DSUDOKU_BIG=1 -DSUDOKU_ALLOW_PRIVATE=1

all: build run

debug: build-debug run-debug

build-debug:
	gcc -o $(FILE_OUT) -g test.c ../sudoku.c $(CFLAGS_DEBUG)

run-debug:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(FILE_OUT)

build:
	gcc -o $(FILE_OUT) test.c ../sudoku.c $(CFLAGS_DEBUG)
run:
	./$(FILE_OUT)
