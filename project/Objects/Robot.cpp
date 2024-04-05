#include "Robot.h"

Robot::Robot()
{
    robotId = 0;
    _currentTile = nullptr;
}

Robot::Robot(int x, int y, int id)
{
    robotId = id;
    this->setPosition(x, y);
}

void Robot::setPosition(Tile *tile)
{
    _currentTile = tile;
}

void Robot::setPosition(int x, int y)
{
    _currentTile = new Tile(x, y);
    _currentTile->setObject(this);
}

void Robot::executeTask(Goal *goal)
{
}

Goal *Robot::getCurrentGoal()
{
}