#pragma once

#include "../TileGraph/Tile.h"
#include "Goal.h"
#include "MapObject.h"

class Robot : public MapObject
{
public:
    Robot();
    Robot(Tile *tile, int id);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);

    bool isFree() { return isFree; }
    void executeTask(Goal *goal);
    Goal *getCurrentGoal(); // If the robot is working, then return the goal robot is working on

    void print() override
    {
        std::cout << "Robot ID: " << robotId << ", Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")" << std::endl;
    }

private:
    int robotId;
    bool isFree;
    Tile *_nextTile;

    Goal *currentGoal; // To know what goal a robot is working on.
    double height;     // Not sure if needed for clearance issues
};