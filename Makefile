includePath=./poco/Net/include/Poco/Net/

all: main.o markov.o node.o
	g++ -o markov main.o markov.o node.o

debug: main.o markov.o node.o
	g++ -g -O0 -v -da -Q -o markov main.o markov.o node.o

main.o: main.cpp markov.o node.o
	g++ -c main.cpp

markov.o: markov.cpp markov.hpp
	g++ -c markov.cpp

node.o: node.cpp node.hpp
	g++ -c node.cpp

clean:
	rm -rf main.o markov.o node.o markov