cohen_p2: main.o contestant.o
	g++ -g -O0 -o cohen_p2 main.o Contestant.o

main.o: main.cpp
	g++ -g -O0 -c main.cpp

contestant.o: Contestant.cpp 
	g++ -g -O0 -c Contestant.cpp

clean: 
	rm -f core *.o 
	rm cohen_p2