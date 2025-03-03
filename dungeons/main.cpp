#include "libstrings.hpp"
#include "libtile.hpp"
#include "dungeon.hpp"
int main(int argc, const char ** argv){
    srand(time(0));
    const size_t height = 100;
    const size_t width =100;
    Dungeon dun = Dungeon::create(width, height,0);
    LibTile::rlImageDrawingState state(width*35, height*35);
    dun.tiles.render(&state);
    state.render_out("test.png");
}