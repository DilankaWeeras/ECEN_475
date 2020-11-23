all: run

run: main.o Graph.o Node.o
	c++ -std=c++17 main.o Stockmeyer.o Node.o -o run

main.o: main.cpp
	c++ -std=c++17 -c main.cpp

Graph.o: Stockmeyer.cpp Stockmeyer.h
	c++ -std=c++17 -c Stockmeyer.cpp

Node.o: Node.cpp Node.h
	c++ -std=c++17 -c Node.cpp

clean:
	rm -f *.o