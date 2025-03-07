targets = libstrings.cpp arena.cpp threads.cpp 
otargets = libstrings.o arena.o threads.o
libs =  
flags = -Wall -Wextra -pedantic -std=c++23 -g3
make: $(targets) 
	clang++ main.cpp $(targets) $(flags) $(libs)
lib:
	clang++ -c $(targets) $(flags) $(libs)
	ar -r libstrings.a $(otargets)
	rm *.o