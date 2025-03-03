files =  main.cpp dungeon.cpp ../libtile/libtile.a
flags = -std=c++20
libs = -lraylib  -L /opt/homebrew/lib  -lprofiler
includes = -I ../libstrings -I ../libtile/ -I /opt/homebrew/include -L /opt/homebrew/lib
make: $(files)
	g++  $(files) $(includes) $(flags) $(libs)

profile: $(files)
	make 
	CPUPROFILE_FREQUENCY=1000000 ./a.out
	pprof --text a.out dump.txt > output.txt