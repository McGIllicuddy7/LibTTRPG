#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include "libtile.hpp"
#include <time.h>
using namespace LibTile;
int main(void){
	const int height =40;
	const int width =40;
	const int pixel_size = 70;
	srand(time(0));
	TileSet tiles;
	tiles.setup(height, width, pixel_size);
	tiles.randomize();
	std::vector<Int2> ints = tiles.path_between(rand()%width, rand()%height, rand()%width, rand()%height);
	tiles.set_list_to(ints, TileWater);
	rlImageDrawingState state = rlImageDrawingState(height*pixel_size, width*pixel_size);
	tiles.render(&state);
	state.render_out("test.png");
	printf("done\n");
}
