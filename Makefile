# sudoku solver makefile
CFLAGS= -Wall -DSUDOKU_VERBOSE

ifdef MUSL
# make MUSL=1
CC     = musl-gcc
CFLAGS += -static
else
CC     = gcc
endif

CFLAGS_DEBUG= $(CFLAGS) -g -DDEBUG -fstack-usage -pedantic -Wextra -Wcast-qual -Wcast-align -Wconversion

LIB    = libsudoku.a
EXE    = main.out

LIB_SRC  = sudoku.c
LIB_OBJ  = $(LIB_SRC:.c=.o)
MAIN_SRC = main.c
MAIN_OBJ = $(MAIN_SRC:.c=.o)


all: $(EXE) run

$(LIB): $(LIB_OBJ)
	ar rcs $@ $^

$(EXE): $(MAIN_OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) -L. -lsudoku

run: $(EXE)
	./$(EXE)

debug: $(EXE)
	$(CC) $(CFLAGS_DEBUG) -o $@ $(MAIN_OBJ) -L. -lsudoku -o $(EXE)
	valgrind ./$(EXE)

tests:
	$(MAKE) -C tests

tests-debug:
	$(MAKE) -C tests debug

clean:
	rm -f main.o main.out main*.su sudoku.o libsudoku.a

.PHONY: tests