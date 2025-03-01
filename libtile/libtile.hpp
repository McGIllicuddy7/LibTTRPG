#pragma once
class DrawingState{
    size_t load_image(std::string path);
    void draw_image();
    size_t unload_image(std::string path);
};
class TilableEntity{
    public:
    virtual void on_render(DrawingState* state) = 0;
};
enum TileType{

};
class Tile{
    bool occupiable;
    public:

    
};