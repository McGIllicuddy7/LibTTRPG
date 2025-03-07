#include "libstrings.hpp"
#include "libtile.hpp"
#include "dungeon.hpp"
#include "threads.hpp"


//without vector being reserved ./a.out  10.94s user 0.04s system 99% cpu 11.037 total
//with vector being reserved ./a.out  10.02s user 0.03s system 98% cpu 10.197 total
//with all vectors in astar being reserved ./a.out  9.89s user 0.04s system 99% cpu 9.937 total
//with vector copies turned into refs ./a.out  6.57s user 0.03s system 97% cpu 6.786 total
//with erase mutating the set in place ./a.out  6.07s user 0.03s system 97% cpu 6.254 total
//without threads ./a.out  67.99s user 110.83s system 331% cpu 53.939 total
//with threads./a.out  78.64s user 7.88s system 723% cpu 11.954 total
//with threads Time taken by function: 11811 milliseconds
//without threads Time taken by function: 54644 milliseconds
//without threads Time taken by function: 11197 milliseconds
//with threads Time taken by function: 2308 milliseconds
int main(int argc, const char ** argv){
    auto start = std::chrono::high_resolution_clock::now();
   // ProfilerStart("dump.txt");
    utils::create_threads();
   // srand(570083267);
    srand(time(0));
    const size_t height =75;
    const size_t width =75;
    constexpr size_t pixel_size = 35;
    const bool is_building = false;
    std::vector<Dungeon *> dungeons = {};
    Dungeon * previous = 0;
    for(int i =0; i<2; i++){
        Dungeon* dun =new Dungeon(Dungeon::create(width, height,pixel_size,is_building,previous)); 
        dungeons.push_back(dun);
        previous = dun;
        
    }

    for(size_t i =0; i<dungeons.size(); i++){
        Dungeon * dun = dungeons[i];
        LibTile::rlImageDrawingState state(width*pixel_size, height*pixel_size);
        dun->tiles.render(&state);
        state.render_out(utils::format("test{}.png", i));
        delete dun;
    }
    utils::join_all_threads();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " milliseconds" << "\n";
}