targets = libtile.cpp AStar.cpp
otargets = libtile.o AStar.o
libs =  -L /opt/homebrew/lib 
flags = -Wall -Wextra -pedantic -std=c++20 -g3 -I../libstrings/
make: $(targets) 
	clang++ main.cpp $(targets) $(flags) $(libs) -lraylib
lib:
	clang++ -c $(targets) $(flags) -Wall -Wextra -pedantic -std=c++20  -O3
	ar -rcs libtile.a $(otargets)
	rm *.o