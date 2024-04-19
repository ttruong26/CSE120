#pragma once

#include "Goal.h"
#include "MapObject.h"
#include <unordered_map>
#include "../graph/Tile.h"
#include "../graph/TileGraph.h"

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
    struct RobotData
    {
        double time;
        double pathDistance;
        Point position;
    };

    Robot();
    Robot(int x, int y, int id, double speed);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);

    bool isFree() { return _isFree; }
    void executeTask(Goal *goal);

    double predictTimeEstimation(Goal *goal); // Find the distance between the robot and the goal
    double updateTimeEstimation();
    Goal *getCurrentGoal(); // If the robot is working, then return the goal robot is working on

    Type getType() const override { return Type::Robot; }

    void print() override
    {
        std::cout << "Robot ID: " << robotId << ", Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")" << std::endl;
    }

private:
    int robotId;
    bool _isFree;
    Tile *_nextTile;
    double _avgSpeed;

    Goal *currentGoal; // To know what goal a robot is working on.
    double height;     // Not sure if needed for clearance issues

    std::unordered_map<Goal *, RobotData> _previousRuns;

    double
    reconstructPath(Tile *end);
};
