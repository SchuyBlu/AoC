
CC=gcc
CFLAGS=-g

part1:part1.c parser.o stack.o
	$(CC) -o $@ $^ $(CFLAGS)

part2:part2.c parser.o stack.o
	$(CC) -o $@ $^ $(CFLAGS)

parser.o:parser.c stack.h
	$(CC) -c $< $(CFLAGS)

stack.o:stack.c stack.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
