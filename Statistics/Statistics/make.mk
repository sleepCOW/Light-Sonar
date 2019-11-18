all: main.cpp
	g++ *.cpp -c -std=c++17 -O2
	rm main.o
	g++ -Wall -o LSonar main.cpp *.o -std=c++17 -O2

clean: 
	$(RM) main