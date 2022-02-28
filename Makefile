OUTPUT_NAME= main.out
CFLAGS= -Wall -Werror
CFLAGS_DEBUG= $(CFLAGS) -DDEBUG
FILES= main.c function.c

all: compile run

compile:
	gcc $(CFLAGS) $(FILES) -o $(OUTPUT_NAME)

debug:
	gcc $(CFLAGS_DEBUG) $(FILES) -o $(OUTPUT_NAME)

run :
	./$(OUTPUT_NAME)