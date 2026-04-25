ARM: Functions.o Driver.o
	g++ Functions.o Driver.o -o ARM

Driver.o: Driver.cpp Functions.h
	g++ -c Driver.cpp

Functions.o: Functions.h Functions.cpp
	g++ -c Functions.cpp

clean:
	rm *.o ARM
