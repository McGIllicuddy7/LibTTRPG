targets = libtile.cpp Astar.cpp
otargets = libtile.o Astar.o
libs =  
flags = -Wall -Wextra -pedantic -std=c++20 -g3
make: $(targets) 
	g++ main.cpp $(targets) $(flags) $(libs) -lraylib
lib:
	gcc -c $(targets) $(flags) $(libs)
	ar -r libtile.a $(otargets)
	rm *.o