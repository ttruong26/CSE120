#include "Tile.h"
#include <cmath>
#include <math.h>

Tile::Tile()
{
    coordinates = Point(0, 0);
}

Tile::Tile(int x, int y)
{
    coordinates = Point(x, y);
}

double Tile::calculateHeuristic(Tile *target)
{
    int dx = this->coordinates._x - target->getX();
    int dy = this->coordinates._y - target->getY();
    return std::sqrt(dx * dx + dy * dy);
}

double Tile::cost(Tile *target)
{
    int dx = std::abs(this->getX() - target->getX());
    int dy = std::abs(this->getY() - target->getY());
    return (dx == 1 && dy == 1) ? std::sqrt(2) : 1;
}

void Tile::resetPathFindingInfo()
{
    g = 0.0;
    h = 0.0;
    f = 0.0;
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