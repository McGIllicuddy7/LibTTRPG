#include "dungeon.hpp"
#include <memory>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using namespace LibTile;
#include <iostream>
struct IntRoom{ 
    unique_ptr<IntRoom> child1;
    unique_ptr<IntRoom> child2;
    IntRoom * parent;
    Int2 location;
    Int2 extent;
    ~IntRoom(){
        //std::cout <<"destroyed\n";
    }
    void find_roots(std::vector<IntRoom *> &rooms){
        if(child1){
            child1->find_roots(rooms);
        }
        if(child2){
            child2->find_roots(rooms);
        }
        if(!child1 &&!child2){
            rooms.push_back(this);
        }
    }
    void split(int min_dimension){
        if(extent.x/2<min_dimension&& extent.y/2<min_dimension){
            return;
        }
        child1 = make_unique<IntRoom>();
        child2 = make_unique<IntRoom>();
        bool horizontal = rand()%2;
        bool rat_x = (extent.x>= extent.y*2);
        bool rat_y = (extent.y>=extent.x*2); 
        if(rat_x) horizontal =true;
        if(rat_y) horizontal = false;
        bool invalid = false;
        int fs = 0;
        const int max_fs = 1000;
        do {
            if(fs == max_fs/2){
                horizontal = !horizontal;
            }
            fs++;
            invalid = false;
            if(horizontal){
                int dx = extent.x/4 + rand()%(extent.x/2);
                if(dx<min_dimension|| (extent.x-dx) <min_dimension){
                    invalid = true;
                    continue;
                }
                child1->location = location;
                child1->extent.y = extent.y;
                child1->extent.x = dx;
                child2->location.x = location.x+dx;
                child2->location.y = location.y;
                child2->extent.y = extent.y;
                child2->extent.x = extent.x-dx; 
            } else{
                int dy = extent.y/4 + rand()%(extent.y/2);
                if(dy<min_dimension|| (extent.y-dy) <min_dimension){
                    invalid = true;
                    continue;
                }
                child1->location = location;
                child1->extent.x = extent.x;
                child1->extent.y = dy;
                child2->location.y = location.y+dy;
                child2->location.x = location.x;
                child2->extent.x = extent.x;
                child2->extent.y = extent.y-dy; 
            }
        } while(invalid&& fs<max_fs);
        if(fs>=max_fs-1){
            child1 = 0;
            child2 = 0;
            return;
        }
        child1->parent = this;
        child2->parent = this;
        child1->split(min_dimension);
        child2->split(min_dimension);
    }
};
Dungeon::Dungeon(){
    
}
Dungeon Dungeon::create(int width, int height, Dungeon * above){
    (void)above;
    int offset = 1;
    constexpr size_t pixel_sz = 35;
    Dungeon out;
    TileSet tiles;
    vector<Room> rooms;
    tiles.setup(width, height,pixel_sz); 
    IntRoom base;
    base.location = {offset,offset};
    base.extent = {width-offset, height-offset};
    base.split(7);
    std::vector<IntRoom*> inter_rooms;
    base.find_roots(inter_rooms);
    for(size_t i =0; i<inter_rooms.size(); i++){
        Room tmp;
        tmp.extent = inter_rooms[i]->extent;
        tmp.location = inter_rooms[i]->location;
        rooms.push_back(tmp);
    }
    for(size_t i =0; i<rooms.size(); i++){
        rooms[i].extent.x -= offset;
        rooms[i].extent.y -=offset;
    }
    for(size_t i =0; i<rooms.size(); i++){
        for(size_t y= rooms[i].location.y; y<rooms[i].location.y+rooms[i].extent.y; y++){
            for(size_t x= rooms[i].location.x; x<rooms[i].location.x+rooms[i].extent.x; x++){
                tiles[y][x].type = TileWood;
                
            }
        }
    }
    out.tiles = tiles;
    out.rooms = rooms;
    return out; 
}