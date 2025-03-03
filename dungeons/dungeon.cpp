#include "dungeon.hpp"
#include <memory>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using namespace LibTile;
#include <iostream>
#include <unordered_set>
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
LibTile::Int2 Dungeon::Room::center(){
    return {location.x+extent.x/2, location.y+extent.y/2};
}
vector<LibTile::Int2> Dungeon::Room::boundary(){
    std::vector<Int2> points;
    int y = -1;
    int x =-1;
    for( x = -1;x<extent.x;x++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    }
    y = extent.y;
    for( x = -1;x<extent.x;x++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    }
    x = -1;
    for( y = -1;y<extent.y;y++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    } 
    x = extent.x;
    for( y = -1;y<extent.y;y++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    } 
    points.push_back({location.x+extent.x, location.y+extent.y});
    return points;
}
std::pair<Int2, Int2> nearest_points(Dungeon::Room & r1, Dungeon::Room & r2){
    auto distance = [](auto a, auto b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);};
    auto p1s = r1.boundary();
    auto p2s = r2.boundary();
    auto c1 = r1.center();
    auto c2 = r2.center();
    Int2 a = p1s[0];
    Int2 b = p2s[0];
    int dist = distance(a,b);
    int cdist = distance(a, c1)+distance(b,c2);
    for(auto i:p1s){
        for(auto j:p2s){
            double d = distance(i,j);
            double cd = distance(i, c1)+distance(j,c2);
            if(d<dist){
                a = i;
                b =j;
                dist = d;
                cdist = cd;
            }
            if(dist == d){
                if(cd<cdist){
                    a = i;
                    b =j;
                    dist = d;
                    cdist = cd; 
                }
            }
        }
    }
    return {a,b};
}
Dungeon Dungeon::create(int width, int height, Dungeon * above){
    (void)above;
    int offset = 10;
    constexpr size_t pixel_sz = 35;
    Dungeon out;
    TileSet tiles;
    vector<Room> rooms;
    tiles.setup(width, height,pixel_sz); 
    IntRoom base;
    base.location = {offset,offset};
    base.extent = {width-offset, height-offset};
    base.split(20);
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
    for(size_t i  =0; i<rooms.size(); i++){
        for(size_t j = i+1; j<rooms.size(); j++){
            std::function<bool(Tile&)> pred = [](auto t){return t.type != TileWood;};
            auto ps = nearest_points(rooms[i], rooms[j]);
            Int2 p1 = ps.first;
            Int2 p2 = ps.second;
            auto p = tiles.path_between_pred(p1.x, p1.y, p2.x, p2.y, pred);
            if(p.size()>0 && p.size()<offset*2+1){
                tiles.set_list_to(p, TileStoneBricks);
            }
        }
    }
    out.tiles = tiles;
    out.rooms = rooms;
    return out; 
}