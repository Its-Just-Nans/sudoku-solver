OUTPUT_NAME=main.out
CFLAGS= -Wall
CFLAGS_DEBUG= $(CFLAGS) -g -DDEBUG -DVERBOSE -fstack-usage
FILES= main.c sudoku.c

all: compile run

compile:
	gcc $(CFLAGS) $(FILES) -o $(OUTPUT_NAME)

debug:
	gcc $(CFLAGS_DEBUG) $(FILES) -o $(OUTPUT_NAME)
	valgrind ./$(OUTPUT_NAME)

run :
	./$(OUTPUT_NAME)

tests:
	$(MAKE) -C tests

tests-debug:
	$(MAKE) -C tests debug

.PHONY: tests