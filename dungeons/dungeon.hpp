#pragma once 
#include <vector>
#include "libtile.hpp"
#include "arena.hpp"
struct Dungeon{
    public:
    struct Room{
        LibTile::Int2 location;
        LibTile::Int2 extent;
        std::string descriptor;
        std::vector<size_t> connections;
        std::vector<LibTile::Int2> up_stair_locations;
        std::vector<LibTile::Int2> down_stair_locations;
    };
    LibTile::TileSet tiles;
    private:
    std::vector<Room> rooms;
    public:
    Dungeon();
    static Dungeon create(int width, int height, Dungeon * above);
};