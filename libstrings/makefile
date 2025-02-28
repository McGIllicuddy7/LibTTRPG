targets = libstrings.cpp arena.cpp 
otargets = libstrings.o arena.o
libs = 
flags = -Wall -Wextra -pedantic -std=c++20 -g3
make: $(targets) 
	g++ main.cpp $(targets) $(flags) $(libs)
lib:
	gcc -c $(targets) $(flags) $(libs)
	ar -r libstrings.a $(otargets)
	rm *.o