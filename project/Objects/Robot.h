#pragma once

#include "../TileGraph/Tile.h"
#include "Goal.h"
#include "MapObject.h"

#include <queue>
#include <unordered_set>

struct CompareTile
{
    bool operator()(Tile *a, Tile *b) const
    {
        return a->f > b->f;
    }
};

class Robot : public MapObject
{
public:
    Robot();
    Robot(int x, int y, int id);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);

    bool isFree() { return _isFree; }
    void executeTask(Goal *goal);

    double findPathDistance(Goal *goal); // Find the distance between the robot and the goal
    Goal *getCurrentGoal();              // If the robot is working, then return the goal robot is working on
    Type getType() const override { return Type::Robot; }

    void print() override
    {
        std::cout << "Robot ID: " << robotId << ", Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")" << std::endl;
    }

    static bool avoidPath(Tile *tile);

private:
    int robotId;
    bool _isFree;
    Tile *_nextTile;

    Goal *currentGoal; // To know what goal a robot is working on.
    double height;     // Not sure if needed for clearance issues

    static bool avoidPath(Tile *tile);

    double reconstructPath(Tile *end);
};
