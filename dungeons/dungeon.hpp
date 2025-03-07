#pragma once 
#include <vector>
#include "libtile.hpp"
#include "arena.hpp"
class Stairs:public LibTile::TileableEntity{
public:
    bool up; 
    void on_render(LibTile::DrawingState* state, size_t x, size_t y, size_t pixel_size);
};
struct Dungeon{
    public:
    struct Room{
        LibTile::Int2 location;
        LibTile::Int2 extent;
        std::string descriptor;
        std::vector<size_t> connections;
        LibTile::Int2 center()const ;
        std::vector<LibTile::Int2> boundary()const ;
        std::vector<LibTile::Int2> boundary_no_corners() const;
        std::vector<LibTile::Int2> all_contained_points()const;
    };
    LibTile::TileSet tiles;
    private:
    std::vector<Room> rooms;
    public:
    std::vector<LibTile::Int2> up_stair_locations;
    std::vector<LibTile::Int2> down_stair_locations;
    LibTile::TileSet sillouette()const;
    friend void setup_stairs(Dungeon& top, Dungeon&bottom, LibTile::TileSet& top_tiles);
    Dungeon();
    static Dungeon create(int width, int height, size_t pixel_sz,bool is_building, Dungeon *above);
};
void setup_stairs(Dungeon& top, Dungeon& bottom);
