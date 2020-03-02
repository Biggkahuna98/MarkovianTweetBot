all: main.o markov.o node.o
	gcc -o markov main.o markov.o node.o

main.o: main.cpp markov.o node.o
	gcc -c main.cpp

markov.o: markov.cpp markov.hpp
	gcc -c markov.cpp

node.o: Node.cpp Node.hpp
	gcc -c Node.cpp