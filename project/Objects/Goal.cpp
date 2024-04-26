#include "Goal.h"

Goal::Goal()
{
    _goalId = "";
    _currentTile = new Tile(0, 0);
}

Goal::Goal(int x, int y, double heading, std::string id)
{
    _goalId = id;
    _heading = heading;
    _currentTile = new Tile();

    // Set the tile with input coordinates
    _currentTile->setPosition(x, y);

    std::shared_ptr<Goal> shared(this);
    _currentTile->setObject(shared);
}

void Goal::setPosition(int x, int y)
{
    _currentTile->setPosition(x, y);
}
