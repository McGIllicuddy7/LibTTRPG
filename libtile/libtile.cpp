
#include "libtile.hpp"
#include "AStar.h"
#include <unordered_map>
using std::unordered_map;
using namespace LibTile;
Tile::Tile(){
    type = TileEmpty;
    is_wall = false;
    child =0;
    occupied = false;
    water = false;
    is_path = false;
    is_floor = false;
    is_door = false;
} 

static size_t hash_point(size_t x, size_t y){
    (void)x;
    (void)y;
    return (rand()%32) >0;
}
static void draw_tile_empty(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    (void)is_wall;
    draw->draw_rectangle(x,y,size, size, 255,0,255);
}
static void draw_tile_grass(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    int c1 = is_wall ? 128:128-64;
    int c2 = is_wall ? 128-32 :128-64-32;
    for(size_t i =y; i<size+y; i++){
        for(size_t j =x; j<size+x; j++){
            int color = hash_point(i,j);
            if(color){
                draw->draw_pixel(j,i,0,c1, 0);
            } else{
                draw->draw_pixel(j,i,0,c2, 0);
            }
        }
    } 
}
static void draw_tile_stone(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    int c1 = is_wall ? 200:200-64;
    int c2 =is_wall ? 128 :128-64;
    for(size_t i =y; i<size+y; i++){
        for(size_t j =x; j<size+x; j++){
            int color =  hash_point(i,j);
            if(color){
                draw->draw_pixel(j,i,c1,c1, c1);
            } else{
                draw->draw_pixel(j,i,c2,c2, c2);
            }
        }
    } 
}
static void draw_tile_dirt(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    int c1 = is_wall ? 64:0;
    int c2 = is_wall ? 32:0;
    int b1 = is_wall ? 32:0;
    int b2 = is_wall ? 16:0;
    for(size_t i =y; i<size+y; i++){
        for(size_t j =x; j<size+x; j++){
            int color =  hash_point(i,j);
            if(color){
                draw->draw_pixel(j,i,c1,b1, 0);
            } else{
                draw->draw_pixel(j,i,c2,b2, 0);
            }
        }
    }  
}
static void draw_tile_water(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    int c1 = is_wall ? 200:200-64;
    int c2 = is_wall ? 128 :128-64;
    for(size_t i =y; i<size+y; i++){
        for(size_t j =x; j<size+x; j++){
            int color =  hash_point(i,j);
            if(color){
                draw->draw_pixel(j,i,0,0, c1);
            } else{
                draw->draw_pixel(j,i,0,0, c2);
            }
        }
    } 
}
static void draw_tile_wood(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    int c1 = is_wall ? 200:200-64;
    int c2 = is_wall ? 128 :128-64;
    int b1 = is_wall ? 130 : 80;
    int b2 = is_wall ? 100 : 50;
    for(size_t i =y; i<size+y; i++){
        for(size_t j =x; j<size+x; j++){
            int color =  hash_point(i,j);
            if((j%35 == 0 || i %7 == 0)){
                draw->draw_pixel(j,i,0,0, 0);
            } else{
                if(color){
                    draw->draw_pixel(j,i,c1,b1, 0);
                } else{
                    draw->draw_pixel(j,i,c2,b2, 0);
                }
            }

        }
    }   
}
static void draw_tile_stone_bricks(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall){
    int c1 = is_wall ? 100:48;
    int c2 = is_wall ? 100 :32;
    for(size_t i =y; i<size+y; i++){
        for(size_t j =x; j<size+x; j++){
            int color =  hash_point(i,j);
            if((j%10 == 0 || i %10 == 0)){
                draw->draw_pixel(j,i,0,0, 0);
            } else{
                if(color){
                    draw->draw_pixel(j,i,c1,c1, c1);
                } else{
                    draw->draw_pixel(j,i,c2,c2, c2);
                }
            }
        }
    }  
}

void Tile::draw(DrawingState * draw,size_t x, size_t y, size_t pixel_size)const{
    static void (*functions[])(DrawingState * draw, size_t x, size_t y, size_t size, bool is_wall)= {draw_tile_empty, draw_tile_grass, draw_tile_stone, draw_tile_dirt, draw_tile_water,draw_tile_wood, draw_tile_stone_bricks};
    functions[type](draw, x, y, pixel_size, is_wall);
    if(this->child)this->child->on_render(draw,x,y,pixel_size);
}
TileSet::TileSet(){
    height = 0;
    width =0;
    pixel_size = 70;
}
void TileSet::setup(size_t in_height, size_t in_width, size_t in_pixel_size){
    height = in_height;
    width = in_width;
    pixel_size = in_pixel_size;
    for(size_t y =0; y<height; y++){
        for(size_t x = 0; x<width; x++){
            tiles.push_back(Tile());
        }
    }
}
void TileSet::randomize(){
    for(size_t y =0; y<height; y++){
        for(size_t x = 0; x<width; x++){
            (*this)[y][x].is_wall = rand()%5 ==0;
            bool t = rand()%5 == 0;
            (*this)[y][x].type = t?  TileGrass : TileWood;
        }
    } 
}
const Tile& TileSet::get(int x, int y)const {
    return tiles[y*width+x];
}
Tile& TileSet::get(int x, int y){
    return tiles[y*width+x];
}
Tile *TileSet::operator[](int y_coord){
    return &tiles[y_coord*width];
}
size_t TileSet::get_height()const{
    return height;
}
size_t TileSet::get_width()const{
    return width;
}
void TileSet::render(DrawingState * draw)const {
    for(size_t y =0; y<height; y++){
        for(size_t x =0; x<width; x++){
            const Tile & a = get(x,y);
            a.draw(draw, x*pixel_size, y*pixel_size, pixel_size);
            
        }
    }
}
std::vector<Int2> TileSet::path_between(int x1, int y1, int x2, int y2){
    std::vector<AStarNode_t> nodes;
    int start = 0;
    int end =0;
    unordered_map<int, Int2> indexs;
    for(size_t y =0; y<height; y++){
        for(size_t x = 0; x<width; x++){
            Int2 p;
            p.x = x;
            p.y = y;
            indexs.insert({y*width+x, p});
            if(x == (size_t)x1 && y == (size_t)y1){
                start = y*width+x;
            }
            if(x == (size_t)x2 &&y ==(size_t)y2){
                end = y*width+x;
            }
            AStarNode_t node;
            std::vector<int> edges;
            std::vector<double> distances;
            double euc_distance = sqrt((double)((x2-x)*(x2-x)+(y2-y)*(y2-y)));
            if(x>0){
                if(!get(x-1,y).is_wall && !get(x-1,y).occupied){
                    edges.push_back(y*width+x-1);
                    distances.push_back(1);
                }
            }
            if(x<width-1){
                if(!get(x+1,y).is_wall && !get(x-1,y).occupied){
                    edges.push_back(y*width+x+1);
                    distances.push_back(1);
                }
            }
            if(y>0){
                if(!get(x,y-1).is_wall && !get(x-1,y).occupied){
                    edges.push_back((y-1)*width+x);
                    distances.push_back(1);
                }
            }
            if(y<height-1){
                if(!get(x,y+1).is_wall && !get(x,y+1).occupied){
                    edges.push_back((y+1)*width+x);
                    distances.push_back(1);
                }
            }
            node.edges = edges;
            node.distances = distances;
            node.euc_distance = euc_distance;
            nodes.push_back(node);
        }
    }
    std::vector<int> path = AStar(nodes, start, end);
    std::vector<Int2> out;
    int x = x1;
    int y = y1;
    std::cout <<x<<" "<<y<<"\n";
    out.push_back({x,y});
    for(size_t i =0; i<path.size(); i++){
        Int2 p = indexs[path[i]];
        out.push_back(p);
    }
    return out;
}
bool TileSet::path_between_exists(int x1, int y1, int x2, int y2){
    if(x1 == y1 && x2 == y2){
        return true;
    } else{
        return path_between(x1,y1,x2,y2).size()>0;
    }
}
std::vector<Int2> TileSet::path_between_pred(int x1, int y1, int x2, int y2,std::function<bool(Tile&)> pred){
    std::vector<AStarNode_t> nodes;
    int start = 0;
    int end =0;
    unordered_map<int, Int2> indexs;
    for(size_t y =0; y<height; y++){
        for(size_t x = 0; x<width; x++){
            Int2 p;
            p.x = x;
            p.y = y;
            indexs.insert({y*width+x, p});
            if(x == (size_t)x1 && y == (size_t)y1){
                start = y*width+x;
            }
            if(x == (size_t)x2 &&y ==(size_t)y2){
                end = y*width+x;
            }
            AStarNode_t node;
            std::vector<int> edges;
            std::vector<double> distances;
            double euc_distance = sqrt((double)((x2-x)*(x2-x)+(y2-y)*(y2-y)));
            if(x>0){
                if(pred(get(x-1, y))){
                    edges.push_back(y*width+x-1);
                    distances.push_back(1);
                }
            }
            if(x<width-1){
                if(pred(get(x+1, y))){
                    edges.push_back(y*width+x+1);
                    distances.push_back(1);
                }
            }
            if(y>0){
                if(pred(get(x, y-1))){
                    edges.push_back((y-1)*width+x);
                    distances.push_back(1);
                }
            }
            if(y<height-1){
                if(pred(get(x, y+1))){
                    edges.push_back((y+1)*width+x);
                    distances.push_back(1);
                }
            }
            node.edges = edges;
            node.distances = distances;
            node.euc_distance = euc_distance;
            nodes.push_back(node);
        }
    }
    std::vector<int> path = AStar(nodes, start, end);
    std::vector<Int2> out;
    int x = x1;
    int y = y1;
    out.push_back({x,y});
    for(size_t i =0; i<path.size(); i++){
        Int2 p = indexs[path[i]];
        out.push_back(p);
    }
    return out;
}
bool TileSet::path_between_exists_pred(int x1, int y1, int x2, int y2,std::function<bool(Tile&)> pred){
    if(x1 == y1 && x2 == y2){
        return true;
    } else{
        return path_between_pred(x1,y1,x2,y2,pred).size()>0;
    }
}
void TileSet::set_list_to(const std::vector<Int2>& points, TileType type, bool is_wall){
    for(size_t j =0; j<points.size(); j++){
        Int2  i = points[j];
        int x = i.x;
        int y = i.y;
        get(x,y).type = type;
        get(x,y).is_wall = is_wall;
    }
}
void TileSet::set_list_to(const std::vector<Int2>& points, TileType type){
    for(size_t j =0; j<points.size(); j++){
        Int2  i = points[j];
        int x = i.x;
        int y = i.y;
        get(x,y).type = type;
    }
}
bool TileSet::borders_type(int x, int y, TileType type)const {
    static const Int2 boundaries[8] = {{-1, 1}, {0, 1}, {1,1}, {-1, 0}, {1,0}, {-1, -1}, {0, -1}, {1,-1}};
    for(int i =0; i<8; i++){
        int xp = x+boundaries[i].x;
        int yp = y+boundaries[i].y;
        if(xp>=0 && yp>=0 && xp<(int)width && yp<(int)height){
            if(get(x,y).type == type){
                return true;
            }
        }
    }
    return false;
}
void rlImageDrawingState::render_out(std::string path){
    ExportImage( m_image,path.c_str());
}
rlImageDrawingState::rlImageDrawingState(size_t height, size_t width){
    m_image = GenImageColor(height, width, BLACK);
}
bool rlImageDrawingState::load_image(std::string path){
    if(m_loaded_images.contains(path)){
        return true;
    }
    Image a= LoadImage(path.c_str());
    m_loaded_images.insert({path,a});
    return true;
}
void rlImageDrawingState::draw_image(const std::string & texture_path,int x, int y, int height, int width){
    if(!m_loaded_images.contains(texture_path)){
        load_image(texture_path);
    }
    Image& img = m_loaded_images[texture_path];
    Rectangle base ={};
    base.x =0;
    base.y =0;
    base.width = m_image.width;
    base.height = m_image.height;
    Rectangle target;
    target.x = x;
    target.y = y;
    target.height = height;
    target.width = width;
    ImageDraw(&m_image,img,base, target, WHITE);

}
void rlImageDrawingState::draw_rectangle(int x, int y, int height, int width, int r, int g, int b){
    Color col;
    col.r = r;
    col.g = g;
    col.b = b;
    col.a = 255;
    ImageDrawRectangle(&m_image, x,y,height, width, col);
}
void rlImageDrawingState::draw_pixel(int x, int y, int r, int g, int b){
    Color col;
    col.r = r;
    col.g = g;
    col.b = b;
    col.a = 255;
    ImageDrawPixel(&m_image, x,y,col);
}
bool rlImageDrawingState::unload_image(std::string path){
    if(!m_loaded_images.contains(path)){
        return false;
    }
    Image a= m_loaded_images[path];
    m_loaded_images.erase(path);
    UnloadImage(a);
    return true;
}
