#pragma once

#include "../TileGraph/Tile.h"

class Wall : public MapObject
{
public:
    Wall();
    Wall(Tile *tile);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);
    Tile *getCurrentPosition();

    void print() override
    {
        std::cout << "Wall Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")" << std::endl;
    }

private:
};