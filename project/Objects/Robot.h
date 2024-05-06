#pragma once

#include "Goal.h"
#include "MapObject.h"
#include <unordered_map>
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
    struct RunTimeInfo
    {
        double _timeTaken;
        Point _robotStartPos;
        Point _goalPosition;
    };

    Robot();
    Robot(int x, int y, int id, double speed);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);
    void moveTo(int x, int y);

    //  Returns a time estimation for the robot to reach the goal.
    // Uses A* algorithm to calculate the shortest path distance.
    // Time is found by dividing the distance by the robot's average speed.
    double predictTimeEstimation(std::shared_ptr<Goal> goal);

    // void setActualTime(std::string goalid, double time_seconds);

    int getId() { return _robotId; }

    // Start the task to Cache Positional Info, finish Task to store the time taken.
    void assignTask(std::shared_ptr<Goal> goal);
    void finishTask(double timeTaken);

    bool isFree() { return _isFree; }

    Goal *getCurrentGoal(); // If the robot is working, then return the goal robot is working on.
    Type getType() const override { return Type::Robot; }

    void print() override
    {
        std::cout << "Robot ID: " << _robotId << ", Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")";
    }

private:
    int _robotId;
    bool _isFree;
    Tile *_nextTile;
    double _avgSpeed;

    double _timeToGoal;
    Goal *currentGoal; // To know what goal a robot is working on.
    RunTimeInfo _currentRun;

    double height; // Not sure if needed for clearance issues

    std::unordered_map<std::string, std::vector<RunTimeInfo>> _previousRuns;

    double weightedAverageTime(std::shared_ptr<Goal> goal);
    double reconstructPath(Tile *end);
    double euclideanDistance(Point a, Point b);
};
