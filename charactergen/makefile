files= main.cpp Abilities.cpp Ancestries.cpp Character.cpp Spellcasting.cpp Utils.cpp personality.cpp grimoire.cpp
flags=-std=c++17 -Wall -Wextra -pedantic -g3
include= -I /opt/homebrew/include -L /opt/homebrew/lib -I../libstrings/
libs=  -lm -lprofiler 
make:$(files)
	g++ $(files) $(flags) $(include) $(libs)
windows:main.cpp Abilities.cpp Ancestries.cpp Character.cpp Spellcasting.cpp Utils.cpp 
	i686-w64-mingw32-c++ main.cpp Abilities.cpp Ancestries.cpp Character.cpp Spellcasting.cpp Utils.cpp -o CharacterGen -g3 -std=c++20

profile: $(files)
	make 
	CPUPROFILE_FREQUENCY=1000000 ./a.out
	pprof --text a.out dump.txt > output.txt