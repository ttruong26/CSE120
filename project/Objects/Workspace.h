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
        std::shared_ptr<Goal> _goal;
        double _time;
    };

    Workspace();
    void loadData();
    void cleanUp();

    std::vector<Robot*> createRobots(int num=5);
    void printGoals();
    Robot* getAssignedRobot(std::string goalId);
    void printAssignmentTable();

    void createAssignmentMap();
    Robot *getRobot(int id);

    // Test implementation for sorting the assignment table
    void updateTable();
    void assignRobots();
    // void addRobotToGoal(Goal *goal, Robot *robot);

private:
    TileGraph *mGraph;                         // Graph to store coordinates for mapObjects
    std::vector<std::shared_ptr<Goal>> _goals; // Holds all of the goals on the workspace, loaded from the map file. Goals have predetermined position coordinates.
    std::vector<std::shared_ptr<Line>> _lines;
    std::vector<std::shared_ptr<Data>> _dataPoints;
    std::vector<Robot *> _robots;
    Point _origin;

    Robot *robot1, *robot2, *robot3;

    std::unordered_map<std::string, std::vector<Robot *>> _assignment; // Robot to goal assignment table. Each goal has all of the robots assigned to it, and we use the predicted time to determine which robot is the best fit for the goal.
    std::unordered_map<std::string, std::shared_ptr<Goal>> _goalsMap;
    
    // Helper function to place loaded objects onto tileMap
    void placeLoadedGoals();
    void placeLoadedObstacles();

    // void assignRobotToGoal(std::shared_ptr<Goal> goal);
};