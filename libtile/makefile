targets = libtile.cpp Astar.cpp
otargets = libtile.o Astar.o
libs =  -L /opt/homebrew/lib  
flags = -Wall -Wextra -pedantic -std=c++20 -g3
make: $(targets) 
	g++ main.cpp $(targets) $(flags) $(libs) -lraylib
lib:
	gcc -c $(targets) $(flags)
	ar -rcs libtile.a $(otargets)
	rm *.o