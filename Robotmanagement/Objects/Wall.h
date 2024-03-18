#pragma once

#include "../TileGraph/Tile.h"

class Wall
{
public:
    Wall();
    Wall(Tile *tile);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);
    Tile *getCurrentPosition();

};