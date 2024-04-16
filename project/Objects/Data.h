#pragma once

// Represents the Obstacle points from the map file under the Data section
#include "MapObject.h"
#include "../graph/Tile.h"
#include <iostream>

class Data : public MapObject
{
public:
    Data();
    Data(int x, int y);

    void setPosition(int x, int y);
    Type getType() const override { return Type::Wall; }

    void print() override
    {
        std::cout << "Data Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")" << std::endl;
    }

private:
};