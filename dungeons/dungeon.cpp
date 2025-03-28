#include "dungeon.hpp"
#include <memory>
#include "threads.hpp"
using std::vector;
using std::unique_ptr;
using std::make_unique;
using namespace LibTile;
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include "AStar.h"
using std::unordered_set;
template<typename T> vector<T> subset(const std::vector<T>&v , std::vector<int> indexes){
    vector<T> out;
    for(auto i: indexes){
        out.push_back(v[i]);
    }
    return out;
}
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
struct RoomConnection{
    Int2 start;
    Int2 end;
    size_t first_index;
    size_t second_index;
    size_t distance()const {
        return (start.x-end.x)*(start.x-end.x)+(start.y-end.y)*(start.y-end.y);
    }
};
Dungeon::Dungeon(){
    
}
LibTile::Int2 Dungeon::Room::center()const {
    return {location.x+extent.x/2, location.y+extent.y/2};
}
vector<Int2>  Dungeon::Room::all_contained_points()const{
    vector<Int2> out;
    for(int y= location.y+2; y<location.y+extent.y-2; y++){
        for(int x =location.x+2;x<location.x+extent.x-2; x++){
            out.push_back({x,y});
        }
    }
    return out;
}
vector<LibTile::Int2> Dungeon::Room::boundary()const {
    std::vector<Int2> points;
    int y = -1;
    int x =0;
    for( x = 0;x<extent.x+1;x++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    }
    y = extent.y;
    for( x = 0;x<extent.x+1;x++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    }
    x = -1;
    for( y = 0;y<extent.y+1;y++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    } 
    x = extent.x;
    for( y = 0;y<extent.y+1;y++){
        int yp = location.y+y;
        int xp = location.x+x;
        points.push_back({xp, yp});
    } 
    points.push_back({location.x+extent.x, location.y+extent.y});
    points.push_back({location.x-1 ,location.y-1});
    return points;
}
vector<LibTile::Int2> Dungeon::Room::boundary_no_corners()const {
    std::vector<Int2> basic = boundary();
    std::vector<Int2> points;
    for(auto i: basic){
        if(i.x == location.x-1 && i.y == location.y-1){

        } else if(i.x == location.x-1 && i.y == location.y+extent.y){

        } else if(i.x == location.x+extent.x && i.y ==location.y-1){

        } else if(i.x == location.x+extent.x && i.y == location.y+extent.y){

        } else{
            points.push_back(i);
        }
    }
    return points;
}
std::pair<Int2, Int2> nearest_points(const Dungeon::Room & r1, const Dungeon::Room & r2){
    auto distance = [](auto a, auto b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);};
    auto p1s = r1.boundary_no_corners();
    auto p2s = r2.boundary_no_corners();
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
vector<Dungeon::Room> create_rooms(int offset, int width, int height, size_t pixel_size,bool is_building, Dungeon * above){
    vector<Dungeon::Room> rooms;
    IntRoom base;
    base.location = {offset,offset};
    base.extent = {width-offset, height-offset};
    base.split(7+offset);
    std::vector<IntRoom*> inter_rooms;
    base.find_roots(inter_rooms);
    for(size_t i =0; i<inter_rooms.size(); i++){
        Dungeon::Room tmp;
        tmp.extent = inter_rooms[i]->extent;
        tmp.location = inter_rooms[i]->location;
        rooms.push_back(tmp);
    }
    for(size_t i =0; i<rooms.size(); i++){
        rooms[i].extent.x -= offset;
        rooms[i].extent.y -=offset;
    }
    return rooms;
}
vector<Dungeon::Room> purge_rooms(const std::vector<Dungeon::Room>& base, int radius,int center_x, int center_y, Dungeon * parent){
    vector<Dungeon::Room> out;
    out.reserve(base.size());
    if(parent){
        LibTile::TileSet tiles = parent->sillouette();
        for(const auto &i:base){
            bool is_valid = true;
            vector<Int2> p = i.all_contained_points();
            for(const auto &j:p){
                if(!tiles.get(j.x, j.y).occupied){
                    is_valid = false;
                    break;
                }
            }
            if(is_valid){
                out.push_back(i);
            }
        }
    } else{
        for(auto & i: base){
            int distance = (i.center().x-center_x)*(i.center().x-center_x)+(i.center().y-center_y)*(i.center().y-center_y);
            if(distance<radius*radius){
                out.push_back(i);
            }
        }
    } 
    return out;
}
bool node_can_reach_all_others(const vector<AStarNode_t> & nodes){
    if(nodes.size() <=1){
        return true;
    }
    for(size_t i =1; i<nodes.size(); i++){
        vector<int> vc = AStar(nodes, 0,i);
        if(vc.size()==0){
            return false;
        }
    }
    for(size_t i =2; i<nodes.size(); i++){
        vector<int> vc = AStar(nodes, 1,i);
        if(vc.size()==0){
            return false;
        }
    }
    return true;
}
vector<AStarNode_t> generate_graphs_from_connections(size_t num_rooms,
    const vector<RoomConnection>&connections, unordered_set<int> to_ignore,int ignore = -1){
    vector<AStarNode_t> nodes;
    for(size_t j=0; j<num_rooms; j++){
        nodes.push_back(AStarNode_t{});
    }
    for(size_t idx = 0;idx<connections.size(); idx++){
        if(to_ignore.contains((int)idx)){
            continue;
        }
        if((int)idx == ignore){
            continue;
        }
        RoomConnection i = connections[idx];
        nodes[i.first_index].edges.push_back(i.second_index);
        nodes[i.first_index].distances.push_back(1);
        nodes[i.second_index].edges.push_back(i.first_index);
        nodes[i.second_index].distances.push_back(1);
    }
    return nodes;
}

std::vector<RoomConnection> setup_rooms(std::vector<Dungeon::Room>& rooms, size_t offset, LibTile::TileSet & tiles,bool is_building){
    std::vector<RoomConnection> connections;
    for(size_t i  =0; i<rooms.size(); i++){
        unordered_set<size_t> used;
        for(size_t k =0; k<4; k++){
            if(rand()%18>4& k>0){
                continue;
            }
            size_t min_distance = 1'000'000'000;
            size_t idx = i+1;
            Int2 connection1;
            Int2 connection2;
            bool set = false;
            for(size_t j = i+1; j<rooms.size(); j++){
                if(used.contains(j)){
                    continue;
                }
                std::pair<Int2, Int2> points = nearest_points(rooms[i], rooms[j]);
                Int2 p1 = points.first;
                Int2 p2 = points.second;
                size_t distance = (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
                if(is_building&& distance != 0){
                    continue;
                }
                if(distance<min_distance){
                    min_distance = distance;
                    idx = j;
                    connection1 = p1;
                    connection2 = p2;
                    set = true;
                }
            }
            if(!set){
                continue;
            }
            if(min_distance>8*offset){
                continue;
            }
            used.insert(idx);
            RoomConnection c1;
            c1.start = connection1;
            c1.end = connection2;
            c1.first_index = i;
            c1.second_index = idx;
            connections.push_back(c1);
            rooms[i].connections.push_back(idx);
            rooms[idx].connections.push_back(i);
        }
    }
    return connections;
}
void draw_connections(const std::vector<RoomConnection> & connections, TileSet& tiles){
    for(auto i: connections){
        auto a= tiles.path_between_pred(i.start.x, i.start.y, i.end.x, i.end.y, [](Tile & a){return !a.is_floor;});
        tiles.set_list_to(a, TileStoneBricks);
        for(int i =0; i<a.size(); i++){
            int x = a[i].x;
            int y = a[i].y;
            tiles.get(x,y).is_path = true;
        }
    }
}
void setup_stairs( Dungeon& bottom,Dungeon& top, LibTile::TileSet& top_tiles){
    size_t ts= top.rooms.size();
    size_t bs = bottom.rooms.size();
    size_t rooms = ts>bs ?bs :ts;
    std::vector<Dungeon::Room> bottom_rooms = bottom.rooms;
    size_t stair_count = (rooms/4) >0 ? rooms/4 : 1;
    std::vector<Int2> stair_locations;
    for(int i =0; i<stair_count; i++){
        do{
            if(bottom_rooms.size() ==0){
                break;
            }
            int r1 = rand()%bottom_rooms.size();
            Dungeon::Room room = bottom_rooms[r1];
            bottom_rooms.erase(bottom_rooms.begin()+r1);
            vector<Int2> usable_points = {};
            vector<Int2> points =room.all_contained_points();
            for(auto i:points){
                if(top_tiles.get(i.x, i.y).is_floor && top_tiles.get(i.x, i.y).occupied == false &&top_tiles.get(i.x, i.y).child == nullptr ){
                    usable_points.push_back(i);
                }
            }
            if(usable_points.size() == 0){
                continue;
            }
            Int2 p = usable_points[rand()%usable_points.size()];
            stair_locations.push_back(p);
            break;
        }while(true);
    }
    for(auto i:stair_locations){
        Stairs stairs;
        stairs.up = true;
        top.down_stair_locations.push_back(i);
        top.tiles.get(i.x, i.y).child = std::make_shared<Stairs>(stairs);
        stairs.up = false;
        bottom.up_stair_locations.push_back(i);
        bottom.tiles.get(i.x, i.y).child = std::make_shared<Stairs>(stairs);
    }
}
Dungeon Dungeon::create(int width, int height,size_t pixel_sz,bool is_building,Dungeon * above){
    (void)above;
    int offset = is_building? 1:5;
    Dungeon out;
    TileSet tiles;
    size_t radius = height/3;
    vector<Room> rooms = create_rooms(offset, width, height, pixel_sz, is_building, above);
    tiles.setup(width, height,pixel_sz); 
    if(is_building){
        rooms = purge_rooms(rooms,radius,width/2, height/2, above);
    }
    for(size_t i =0; i<rooms.size(); i++){
        for(size_t y= rooms[i].location.y; y<rooms[i].location.y+rooms[i].extent.y; y++){
            for(size_t x= rooms[i].location.x; x<rooms[i].location.x+rooms[i].extent.x; x++){
                tiles[y][x].type = TileWood;
                tiles.get(x,y).is_floor = true;
            }
        }
    }
    auto connections = setup_rooms(rooms, offset, tiles, is_building);
    draw_connections(connections, tiles);
    for(const Room&i: rooms){
        vector<Int2> bound = i.boundary();
        for(Int2 p: bound){
        Tile & t = tiles.get(p.x, p.y);
            if(t.type == TileEmpty){
                t.type = TileStoneBricks;
                t.is_wall = true;
            }
        }
    }
    for(size_t j =0; j<tiles.get_height(); j++){
        for(size_t i =0; i<tiles.get_width(); i++){
            if(tiles.get(i,j).type == TileEmpty){
                bool borders = false;
                for(int y =-1; y<2; y++){
                    if(borders){
                        break;
                    }
                    for(int x =-1; x<2; x++){
                        if((x == 0 && y == 0) || (x+i)<0 || (x+i)>=tiles.get_width()|| (y+j)<0 || (y+j)>=tiles.get_width()){
                            continue;
                        }
                        if(tiles.get(i+x,j+y).is_floor|| tiles.get(i+x,j+y).is_path){
                            borders = true; 
                            break;
                        }
                    }
                }
                if(borders){
                    tiles.get(i,j).type = TileStoneBricks;
                    tiles.get(i,j).is_wall = true;
                }
            }
        }
    }
    out.tiles = tiles;
    out.rooms = rooms;
    if(above){
        printf("called setup\n");
        setup_stairs(out, *above, above->tiles);
    }

    return out; 
}
LibTile::TileSet Dungeon::sillouette()const{
    LibTile::TileSet out = tiles;
    for(size_t y =0; y<out.get_height(); y++){
        for(size_t x =0; x<out.get_width(); x++){
            if(out.get(x,y).is_floor || out.get(x,y).is_door || out.get(x,y).is_path || out.get(x,y).is_wall){
                out.get(x,y).type = TileEmpty;
                out.get(x,y).occupied = true;
                out.get(x,y).is_floor = false;
                out.get(x,y).is_path = false;
                out.get(x,y).is_wall = false;
                out.get(x,y).is_door = false;
            } else{
                out.get(x,y).type = TileEmpty;
                out.get(x,y).occupied = false;
                out.get(x,y).is_floor = false;
                out.get(x,y).is_path = false;
                out.get(x,y).is_wall = false;
                out.get(x,y).is_door = false;
            }
        }
    }
    return out; 
}

LibTile::TileSet Dungeon::sillouette_only_floors()const{
    LibTile::TileSet out = tiles;
    for(size_t y =0; y<out.get_height(); y++){
        for(size_t x =0; x<out.get_width(); x++){
            if(out.get(x,y).is_floor){
                out.get(x,y).type = TileEmpty;
                out.get(x,y).occupied= true;
                out.get(x,y).is_floor = false;
                out.get(x,y).is_path = false;
                out.get(x,y).is_wall = false;
                out.get(x,y).is_door = false;
            } else{
                out.get(x,y).type = TileEmpty;
                out.get(x,y).occupied = false;
                out.get(x,y).is_floor = false;
                out.get(x,y).is_path = false;
                out.get(x,y).is_wall = false;
                out.get(x,y).is_door = false;
            }
        }
    }
    return out; 
}
void Stairs::on_render(LibTile::DrawingState * state, size_t x, size_t y, size_t pixel_size){
    if(up)state->draw_rectangle(x, y, pixel_size, pixel_size, 255, 0,0);
    else state->draw_rectangle(x, y, pixel_size, pixel_size, 0,0,255);
}
