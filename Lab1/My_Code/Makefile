all: run

run: main.o Graph.o Node.o
	c++ -std=c++17 main.o Graph.o Node.o -o run

main.o: main.cpp
	c++ -std=c++17 -c main.cpp

Graph.o: Graph.cpp Graph.h
	c++ -std=c++17 -c Graph.cpp

Node.o: Node.cpp Node.h
	c++ -std=c++17 -c Node.cpp

clean:
	rm -f *.o