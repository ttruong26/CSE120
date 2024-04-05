#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "../Utility.h"
#include "../Objects/MapObject.h"

class Tile
{
public:
    // Tile constructors for placing a tile on x-y grid
    Tile();
    Tile(int x, int y);

    void setPosition(int x, int y);
    Point getPosition();
    int getX();
    int getY();

        void setObject(MapObject *object);
    MapObject *getObject();

    // To check what type of mapObject is placed on the tile
    bool isRobot() const;
    bool isGoal() const;
    bool isWall() const;
    bool isFree() const;

    // AStar Properties
    int g = 0;
    int h = 0;
    int f = 0;
    Tile *parent = nullptr;
    void calculateHeuristic(const Point &target);
    void resetPathFindingInfo();

    void Print()
    {
        std::cout << "(" << coordinates._x << ", " << coordinates._y << ") ";
    }

private:
    Point coordinates;

    // Tile can either hold a robot, goal or wall element
    MapObject *_object;
};

#endif
