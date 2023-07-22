CXX = g++
CXXFLAGS = -Wall 

all: main

main: ticTacToe.cpp ticTacToe.o
	$(CXX) $(CXXFLAGS) ticTacToe.cpp -o ticTacToe.exe