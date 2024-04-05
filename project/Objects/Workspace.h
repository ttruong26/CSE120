#pragma once

#include "../TileGraph/TileGraph.h"
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
    void placeLoadedLines();
    void printGoals();

    void updateTable();
    void addRobotToGoal(Goal *goal, Robot *robot);

private:
    TileGraph *graph;          // Graph to hold coordinates for mapObjects
    std::vector<Goal *> goals; // Holds all of the goals on the workspace, loaded from the map file. Goals have predetermined position coordinates.
    std::vector<Line *> lines;
};