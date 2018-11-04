all: main.o BTree.o
	g++ main.o BTree.o -o lab4
main.o: ./Source/main.cpp
	g++ -c ./Source/main.cpp
BTree.o: ./Source/BTree.hpp
	g++ -c ./Source/BTree.cpp
clean:
	rm main.o BTree.o