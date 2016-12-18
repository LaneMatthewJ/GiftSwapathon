CC = g++

all: swapathon

swapathon: main.cpp
	$(CC) -std=c++11 -o swapathon *.cpp

clean:
	/bin/rm -f *.o swapathon
