#pragma once
#include <vector>
#include <unordered_map>
#include <raylib.h>
#include <functional>
#include <memory>
#include "libstrings.hpp"
namespace LibTile{
struct Int2{
    int x;
    int y;
};

class DrawingState{
    public:
    virtual bool load_image(std::string path) = 0;
    virtual void draw_image(const std::string & texture_path,int x, int y, int height, int width) = 0;
    virtual void draw_pixel(int x, int y, int r, int g, int b)= 0;
    virtual void draw_rectangle(int x, int y, int height, int width, int r, int g, int b) = 0;
    virtual bool unload_image(std::string path) = 0;
};
class TileableEntity{
    public:
    virtual void on_render(DrawingState* state,size_t x, size_t y, size_t pixel_size) = 0;
    virtual ~TileableEntity() = 0;
};
enum TileType:uint8_t{
    TileEmpty,TileGrass, TileStone, TileDirt, TileWater,TileWood, TileStoneBricks,TileCarpetRed, TileCarpetBlue,TileCarpetGreen,TileCarpetPurple,
};
struct Tile{
    TileType type;
    bool occupied;
    bool is_wall;
    bool water;
    bool is_path;
    bool is_floor;
    bool is_empty;
    bool is_door;
    std::shared_ptr<TileableEntity> child;
    Tile();
    void draw(DrawingState * draw,size_t x, size_t y, size_t pixel_size)const ;
};
constexpr size_t tile_size = sizeof(Tile);
class TileSet{
    size_t height;
    size_t width;
    size_t pixel_size;
    std::vector<Tile> tiles;
    public:
    TileSet();
    void setup(size_t in_height, size_t in_width, size_t pixel_size);
    void randomize();
    size_t get_height()const;
    size_t get_width()const ;
    void render(DrawingState * draw)const ;
    const Tile& get(int x, int y)const;
    Tile& get(int x, int y);
    Tile *operator[](int y_coord);
    std::vector<Int2> path_between(int x1, int y1, int x2, int y2);
    bool path_between_exists(int x1, int y1, int x2, int y2);
    std::vector<Int2> path_between_pred(int x1, int y1, int x2, int y2, std::function<bool(Tile&)>);
    bool path_between_exists_pred(int x1, int y1, int x2, int y2,std::function<bool(Tile&)>);
    void set_list_to(const std::vector<Int2>& points, TileType type, bool is_wall);
    void set_list_to(const std::vector<Int2>& points, TileType type);
    bool borders_type(int x, int y, TileType type) const;
};
class rlImageDrawingState:public DrawingState{
    Image m_image;
    std::unordered_map<std::string, Image> m_loaded_images;
    public: 
    rlImageDrawingState(size_t height, size_t width);
    void render_out(std::string path);
    bool load_image(std::string path);
    void draw_image(const std::string & texture_path,int x, int y, int height, int width);
    void draw_pixel(int x, int y, int r, int g, int b);
    void draw_rectangle(int x, int y, int height, int width, int r, int g, int b);
    bool unload_image(std::string path);
};
}