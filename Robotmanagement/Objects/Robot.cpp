#include "Robot.h"

Robot::Robot()
{
    robotId = 0;
    currentTile = nullptr;
}

Robot::Robot(Tile *tile, int id)
{
    robotId = id;
    currentTile = tile;
}

void Robot::setPosition(Tile *tile)
{
    currentTile = tile;
}

void Robot::setPosition(int x, int y)
{
    currentTile->setPosition(x, y);
}

std::pair<int, int> Robot::getCurrentPosition()
{
    return currentTile->getPosition();
}

void Robot::executeTask(Goal *goal)
{
}

Goal *Robot::getCurrentGoal()
{
}