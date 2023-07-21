CC = g++
CFLAGS = -Wall 

all: main

main: ticTacToe.cpp ticTacToe.o
	$(CC) $(CFLAGS) ticTacToe.cpp -o ticTacToe.exe