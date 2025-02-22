OUTPUT_NAME= main.out
CFLAGS= -Wall
CFLAGS_DEBUG= $(CFLAGS) -DDEBUG -DVERBOSE -fstack-usage
FILES= main.c function.c

all: compile run

compile:
	gcc $(CFLAGS) $(FILES) -o $(OUTPUT_NAME)

debug:
	gcc $(CFLAGS_DEBUG) $(FILES) -o $(OUTPUT_NAME)

run :
	./$(OUTPUT_NAME)