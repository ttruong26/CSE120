#pragma once

#include "../TileGraph/Tile.h"
#include "Goal.h"

class Robot
{
public:
    Robot();
    Robot(Tile *tile, int id);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);
    std::pair<int, int> getCurrentPosition();

    bool isFree() { return isFree; }
    void executeTask(Goal *goal);
    Goal *getCurrentGoal(); // If the robot is working, then return the goal robot is working on
private:
    int robotId;
    bool isFree;
    Tile *currentTile, nextTile;

    Goal *currentGoal; // To know what goal a robot is working on.
    double height;     // Not sure if needed for clearance issues
};
