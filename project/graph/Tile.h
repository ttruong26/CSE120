#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "../include/Utility.h"
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

    void setObject(std::shared_ptr<MapObject> object);
    MapObject *getObject();

    // To check what type of mapObject is placed on the tile
    bool isRobot() const;
    bool isGoal() const;
    bool isWall() const;
    bool isFree() const;

    // AStar Properties
    double g = 0.0;
    double h = 0.0;
    double f = 0.0;
    Tile *parent = nullptr;
    double calculateHeuristic(Tile *target);
    double cost(Tile *target);

    void resetPathFindingInfo();

    void Print()
    {
        std::cout << "(" << coordinates._x << ", " << coordinates._y << ") ";
    }

private:
    Point coordinates;

    // Tile can either hold a robot, goal or wall element
    std::shared_ptr<MapObject> _object;
};

#endif
