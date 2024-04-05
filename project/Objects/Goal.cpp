#include "Goal.h"

Goal::Goal()
{
    _goalId = "";
    _currentTile = new Tile(0, 0);
}

Goal::Goal(Tile *tile, int id)
{
    _goalId = id;
    _currentTile = tile;
}

Goal::Goal(int x, int y, double heading, std::string id)
{
    _goalId = id;
    _heading = heading;
    _currentTile = new Tile();

    // Set the tile with goal information
    _currentTile->setPosition(x, y);
    _currentTile->setObject(this);
}

void Goal::setPosition(Tile *tile)
{
    _currentTile = tile;
}

void Goal::setPosition(int x, int y)
{
    _currentTile->setPosition(x, y);
}
