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

    void printGoals();

    void createAssignmentMap();
    void assignRobotsToGoals();

    void updateTable();
    void addRobotToGoal(Goal *goal, Robot *robot);

private:
    TileGraph *mGraph;                         // Graph to store coordinates for mapObjects
    std::vector<std::unique_ptr<Goal>> _goals; // Holds all of the goals on the workspace, loaded from the map file. Goals have predetermined position coordinates.
    std::vector<std::unique_ptr<Line>> _lines;
    std::vector<std::unique_ptr<Data>> _dataPoints;
    std::vector<Robot *> _robots;

    Robot *robot1, *robot2, *robot3;

    std::unordered_map<Goal *, std::vector<Robot *>> _assignment; // Robot to goal assignment table. Each goal has all of the robots assigned to it, and we use the predicted time to determine which robot is the best fit for the goal.

    // Helper function to place loaded objects onto tileMap
    void placeLoadedGoals();
    void placeLoadedObstacles();
};