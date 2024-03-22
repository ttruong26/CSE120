#include "Tile.h"

Tile::Tile()
{
    coordinates = Point(0, 0);
}

Tile::Tile(int x, int y)
{
    coordinates = Point(x, y);
}

void Tile::calculateHeuristic(const Point &target)
{
    this->h = (abs(coordinates._x - target._x) + abs(coordinates._y - target._y));
    this->f = this->g + this->h;
}

void Tile::resetPathFindingInfo()
{
    g = 0;
    h = 0;
    f = 0;
    parent = nullptr;
}

void Tile::setPosition(int x, int y)
{
    coordinates._x = x;
    coordinates._y = y;
}

void Tile::setObject(MapObject *object)
{
    _object = object;
}

MapObject *Tile::getObject()
{
    return _object;
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

bool Tile::isRobot() const
{
    return _object != nullptr && _object->getType() == MapObject::Type::Robot;
}

bool Tile::isGoal() const
{
    return _object != nullptr && _object->getType() == MapObject::Type::Goal;
}

bool Tile::isWall() const
{
    return _object != nullptr && _object->getType() == MapObject::Type::Wall;
}

bool Tile::isFree() const
{
    return _object == nullptr;
}