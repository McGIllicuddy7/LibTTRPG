files =  main.cpp dungeon.cpp ../libstrings/libstrings.a ../libtile/AStar.cpp ../libtile/libtile.cpp
flags = -std=c++20 
libs = -lraylib  -L /opt/homebrew/lib  -lprofiler 
includes = -I ../libstrings -I ../libtile/ -I /opt/homebrew/include -L /opt/homebrew/lib
make: $(files)
	clang++  $(files) $(includes) $(flags) $(libs)
release: $(files)
	clang++  $(files) $(includes) $(flags) $(libs) -O3
profile: $(files)
	make 
	CPUPROFILE_FREQUENCY=1000000 ./a.out
	pprof --text a.out dump.txt > output.txt