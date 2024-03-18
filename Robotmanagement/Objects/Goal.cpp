#include "Goal.h"

Goal::Goal()
{
    _goalId = "";
    currentTile = new Tile(0, 0);
}

Goal::Goal(Tile *tile, int id)
{
    _goalId = id;
    currentTile = tile;
}

Goal::Goal(int x, int y, double heading, std::string id)
{
    _goalId = id;
    _heading = heading;
    currentTile = new Tile();
    currentTile->setPosition(x, y);
}

void Goal::setPosition(Tile *tile)
{
    currentTile = tile;
}

void Goal::setPosition(int x, int y)
{
    currentTile->setPosition(x, y);
}

Tile *Goal::getCurrentPosition()
{
    return currentTile;
}
