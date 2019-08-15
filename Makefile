CC=gcc
CFLAGS=-O3

all:mincut

mincut:main.o mincut.o
	$(CC) $(CFLAGS) main.o mincut.o -o mincut

main.o:main.c mincut.o
	$(CC) $(CFLAGS) -c main.c -o main.o


mincut.o:mincut.c mincut.h
	$(CC) $(CFLAGS) -c mincut.c -o mincut.o


