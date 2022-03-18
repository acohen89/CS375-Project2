Submission: main.o contestant.o
	g++ -g -O0 -o Submission main.o Contestant.o

main.o: main.cpp
	g++ -g -O0 -c main.cpp

contestant.o: Contestant.cpp 
	g++ -g -O0 -c Contestant.cpp

clean: 
	rm -f core *.o 
	rm Submission