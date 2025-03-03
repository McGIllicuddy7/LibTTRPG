#include "libstrings.hpp"
#include "libtile.hpp"
#include "dungeon.hpp"
#include <gperftools/profiler.h>

//without vector being reserved ./a.out  10.94s user 0.04s system 99% cpu 11.037 total
//with vector being reserved ./a.out  10.02s user 0.03s system 98% cpu 10.197 total
//with all vectors in astar being reserved ./a.out  9.89s user 0.04s system 99% cpu 9.937 total
//with vector copies turned into refs ./a.out  6.57s user 0.03s system 97% cpu 6.786 total
int main(int argc, const char ** argv){
    ProfilerStart("dump.txt");
    srand(570083267);
    const size_t height = 100;
    const size_t width =100;
    Dungeon dun = Dungeon::create(width, height,0);
    LibTile::rlImageDrawingState state(width*35, height*35);
    dun.tiles.render(&state);
    state.render_out("test.png");
}