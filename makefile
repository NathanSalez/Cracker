all : testBruteforce.exe

testBruteforce.exe : Bruteforce.o BruteforceSimple.o BruteforceDictionnary.o
	g++ *.o main.cpp -o testBruteforce.exe

Bruteforce.o :
	g++ -c Bruteforce.cpp

BruteforceSimple.o :
	g++ -c BruteforceSimple.cpp

BruteforceDictionnary.o :
	g++ -c BruteforceDictionnary.cpp 

clean :
	rm *.o *.exe
