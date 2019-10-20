all : testBruteforce.exe

testBruteforce.exe : Cracker.o BruteforceSimple.o BruteforceDictionnary.o
	g++ *.o main.cpp -o testBruteforce.exe

Cracker.o :
	g++ -c Cracker.cpp

BruteforceSimple.o :
	g++ -c BruteforceSimple.cpp

BruteforceDictionnary.o :
	g++ -c BruteforceDictionnary.cpp 

clean :
	rm *.o *.exe
