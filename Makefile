CC = gcc
CFLAGS = -Wall -std=c99 -g
LIBS = -lm

all: program test_program

program:
	$(CC) $(CFLAGS) -I./include src/main.c src/lrps.c -o program $(LIBS)

test_program:
	$(CC) $(CFLAGS) -I./include test/test.c src/lrps.c -o test_program $(LIBS)

clean:
	rm -f program test_program

run: program
	./program

test-run: test_program
	./test_program

.PHONY: all clean run test-run