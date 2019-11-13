all: Statistics.cpp
	g++ *.cpp -c -std=c++17
	rm Statistics.o
	g++ -Wall -o john Statistics.cpp *.o -std=c++17

clean: 
	$(RM) john