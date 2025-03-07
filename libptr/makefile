targets = 
otargets = libtile.o Astar.o
libs =  -L /opt/homebrew/lib -I ../libstrings/ -I ../libptr/ -fsanitize=address
flags = -Wall -Wextra -pedantic -std=c++20 -g3
make: $(targets) 
	clang++ main.cpp $(targets) $(flags) $(libs) -lraylib
lib:
	clang++ -c $(targets)  -Wall -Wextra -pedantic -std=c++20  -O3
	ar -rcs libtile.a $(otargets)
	rm *.o
