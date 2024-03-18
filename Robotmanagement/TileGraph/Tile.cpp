#include "Tile.h"

Tile::Tile()
{
    coordinates = Point(0, 0);
}

Tile::Tile(int x, int y)
{
    coordinates = Point(x, y);
}

void Tile::setPosition(int x, int y)
{
    coordinates._x = x;
    coordinates._y = y;
}

void Tile::setRobot(Robot *robot)
{
    mRobot = robot;
}

void Tile::setGoal(Goal *goal)
{
    mGoal = goal;
}

Point Tile::getPosition()
{
    return coordinates;
}

int Tile::getX()
{
    return coordinates._x;
}

int Tile::getY()
{
    return coordinates._y;
}
