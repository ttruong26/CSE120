#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm> // for std::sort

#include "../TileGraph/TileGraph.h"
#include "../Objects/Goal.h"
#include "../static/MapLoader.h"
#include "../Objects/Robot.h"

class Workspace
{
public:
    Workspace();
    void loadData();
    void placeLoadedGoals();
    void printGoals();
    void updateTable();
    void addRobotToGoal(Goal* goal, Robot* robot);

private:
    TileGraph *graph;
    std::vector<Goal *> goals;
    std::vector<Line> lines;
    std::unordered_map<Goal*, std::vector<Robot*>> goalRobotMap;
};