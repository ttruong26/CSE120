#pragma once

#include "../graph/TileGraph.h"
#include "../static/MapLoader.h"
#include "Robot.h"

#include <unordered_map>
#include <algorithm>

class Workspace
{
public:
    struct RobotGoalPrediction
    {
        Robot *_robot;
        double _time;
    };

    Workspace();
    void loadData();
    void cleanUp();

    std::vector<Robot *> createRobots(int num = 5);
    Robot *getAssignedRobot(std::string goalId);
    std::vector<std::shared_ptr<Goal>> getGoals() { return _goals; }

    void assignAllRobots();
    void assignRobotToGoal(std::string goalId);

    void printGoals();
    void printAssignmentTable();

    void createAssignmentTable();
    void sortAssignmentTable();

    Robot *getRobot(int id);

private:
    TileGraph *mGraph;                         // Graph to store coordinates for mapObjects
    std::vector<std::shared_ptr<Goal>> _goals; // Holds all of the goals on the workspace, loaded from the map file. Goals have predetermined position coordinates.
    std::vector<std::shared_ptr<Line>> _lines;
    std::vector<std::shared_ptr<Data>> _dataPoints;
    std::vector<Robot *> _robots;
    Point _origin;

    std::unordered_map<std::string, std::vector<RobotGoalPrediction>> _assignment; // Robot to goal assignment table. Each goal has all of the robots assigned to it, and we use the predicted time to determine which robot is the best fit for the goal.
    std::unordered_map<std::string, std::shared_ptr<Goal>> _goalsMap;

    // Helper function to place loaded objects onto tileMap
    void placeLoadedGoals();
    void placeLoadedObstacles();
};