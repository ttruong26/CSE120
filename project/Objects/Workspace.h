#pragma once

#include "../graph/TileGraph.h"
#include "../static/MapLoader.h"
#include "Robot.h"

#include <unordered_map>
#include <algorithm>

class Workspace
{
public:
    Workspace();
    void loadData();

    // Test functions
    void placeLoadedGoals(); // Test function to place goals on the graph
    void placeLoadedObstacles();
    void printGoals();

    void updateTable();
    void addRobotToGoal(Goal *goal, Robot *robot);

private:
    TileGraph *mGraph;         // Graph to store coordinates for mapObjects
    std::vector<Goal *> goals; // Holds all of the goals on the workspace, loaded from the map file. Goals have predetermined position coordinates.
    std::vector<Line *> lines;
    std::vector<Data *> dataPoints;

    std::unordered_map<Goal *, std::vector<Robot *>> goalRobotMap;
};