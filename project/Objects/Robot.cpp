#include "Robot.h"

Robot::Robot()
{
    robotId = 0;
    _currentTile = nullptr;
}

Robot::Robot(Tile *tile, int id)
{
    robotId = id;
    _currentTile = tile;
}

void Robot::setPosition(Tile *tile)
{
    _currentTile = tile;
}

void Robot::setPosition(int x, int y)
{
    _currentTile->setPosition(x, y);
}

void Robot::executeTask(Goal *goal)
{
}

Goal *Robot::getCurrentGoal()
{
}