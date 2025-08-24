FILE_OUT=test.out
CFLAGS_DEBUG= $(CFLAGS) -g -DDEBUG -DVERBOSE -fstack-usage -pedantic -Wall -Wextra -Wcast-qual -Wcast-align -Wconversion

all: build run

debug: build-debug run-debug

build-debug:
	gcc -o $(FILE_OUT) -g test.c ../sudoku.c $(CFLAGS_DEBUG)

run-debug:
	valgrind ./$(FILE_OUT)

build:
	gcc -o $(FILE_OUT) test.c ../sudoku.c $(CFLAGS_DEBUG)
run:
	./$(FILE_OUT)
