targets = libstrings.cpp arena.cpp 
libs = 
flags = -Wall -Wextra -pedantic -std=c++20 -g3
make: $(targets) 
	g++ main.cpp $(targets) $(flags) $(libs)
lib:
	gcc -c $(targets) $(flags) $(libs)
	ar -rcs libstrings.a *.o
	rm *.o