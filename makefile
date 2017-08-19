main: main.o MCTS.o
	g++ -std=c++11 main.o MCTS.o -o exe
main.o: main.cpp 
	g++ -std=c++11 -g -c main.cpp
MCTS.o:	MCTS.cpp MCTS.hpp
	g++ -std=c++11 -g -c MCTS.cpp
clean:
	rm *.o
