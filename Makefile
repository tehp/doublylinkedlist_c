# Makefile for doubly linked list

CC=gcc
CFLAGS=-ansi -ggdb -g -Wall

dll:
	$(CC) $(CFLAGS) main.c -o dll

run: clean dll
	./dll

clean:
	rm -f *.o dll && rm -rf dll.dSYM
