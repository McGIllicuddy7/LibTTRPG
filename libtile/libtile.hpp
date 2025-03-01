#pragma once
class DrawingState{

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