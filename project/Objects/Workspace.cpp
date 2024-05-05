#include "Workspace.h"

Workspace::Workspace()
{
    mGraph = new TileGraph();
}

void Workspace::loadData()
{
    // Load tile Graph
    MapLoader::LoadMap(*mGraph, _goals, _lines, _dataPoints, "mapfiles/test1.map");
    MapObject::_mGraph = mGraph;
    this->_origin = mGraph->getOrigin();
    mGraph->print();
    std::cout << std::endl;

    this->placeLoadedGoals();
    this->placeLoadedObstacles();
    this->createRobots();

    // Once robots are and goals are loaded and placed on graph, we can create the assignment map
    this->createAssignmentTable();
}

std::vector<Robot *> Workspace::createRobots(int num)
{
    for (int i = 0; i < num; i++)
    {
        Robot *robot = new Robot(_origin._x, _origin._y, i, 1200);
        mGraph->placeObject(robot);
        _robots.push_back(robot);
    }

    return _robots;
}

void Workspace::createAssignmentTable()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        std::string goalName = _goals[i]->getGoalId();
        _assignment[goalName] = std::vector<Robot *>();
        _goalsMap[goalName] = _goals[i];
    }

    // We will assign every robot to every goal, to find the predicted time for each robot and find the best fit
    for (int i = 0; i < _goals.size(); i++)
    {
        for (auto robot : _robots)
            _assignment[_goals[i]->getGoalId()].push_back(robot);
    }
}

void Workspace::printGoals()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        _goals[i]->print();
    }
}

void Workspace::printAssignmentTable()
{
    // Print the assignment table
    for (auto &pair : _assignment)
    {
        std::string goalName = pair.first;
        std::vector<Robot *> &robotList = pair.second;
        std::cout << goalName << " | ";

        for (int i = 0; i < robotList.size(); i++)
        {
            robotList.at(i)->print();
            std::cout << ", ";
        }
        std::cout << "|" << std::endl;
    }
}

Robot *Workspace::getAssignedRobot(std::string goalId)
{
    /*
    static int i = -1;
    std::cout << "Returning assigned robot " << i << " " << _robots.size() << std::endl;
    return _robots[++i];
    */

    for (auto &pair : _assignment)
    {
        if (pair.first == goalId)
        {
            for (auto robot : pair.second)
            {
                if (robot->isFree())
                {
                    return robot;
                }
            }
        }
    }
    return NULL;
}

void Workspace::assignRobotToGoal(std::string goalId)
{
    Robot *robot = getAssignedRobot(goalId);
    if (robot != NULL)
    {
        std::shared_ptr<Goal> goal = _goalsMap[goalId];
        std::cout << "Robot " << robot->getId() << " is assigned to " << goalId << std::endl;
        robot->assignTask(goal);
    }
}

void Workspace::assignAllRobots()
{
    for (auto &pair : _assignment)
    {
        assignRobotToGoal(pair.first);
    }
}

void Workspace::placeLoadedObstacles()
{

    for (int i = 0; i < _lines.size(); i++)
    {
        if (i == 17) // The 17th line is out of bounds of the workspace
        {
            continue;
        }
        mGraph->placeObject(_lines[i].get());
    }

    for (int i = 0; i < _dataPoints.size(); i++)
    {
        mGraph->placeObject(_dataPoints[i].get());
    }
}

void Workspace::placeLoadedGoals()
{
    for (int i = 0; i < _goals.size(); i++)

    {
        mGraph->placeObject(_goals[i].get());
    }
}

void Workspace::cleanUp()
{
    delete mGraph;
    delete robot1;
    delete robot2;
}

void Workspace::sortAssignmentTable()
{

    // Iterate through each goal in the map
    for (auto &pair : _assignment)
    {
        std::string goal = pair.first;
        std::vector<Robot *> &robotsUpdatedList = pair.second;
        std::cout << std::endl;

        // Calculate distance of each robot from the goal
        // Calculate distance of each robot from the goal
        std::sort(robotsUpdatedList.begin(), robotsUpdatedList.end(), [this, goal](Robot *a, Robot *b)
                  {
                      auto goalIter = _goalsMap.find(goal);
                      if (goalIter != _goalsMap.end())
                          return a->predictTimeEstimation(goalIter->second) < b->predictTimeEstimation(goalIter->second);
                      else
                          std::cout << "Goal not found in goal map" << std::endl;
                      return true;
                      //  from robot to destination.
                  });
        // Assign the robot with the shortest predicted time to the goal
        // robot[0]->assign(goal);
    }

    std::cout << "Robots assigned to goals." << std::endl;
}

/*
    This function will assign robots to goals based on the predicted time to reach the goal.
    The robot with the shortest predicted time will be assigned to the goal.
*/

/*
// We will assume that any robot can work on any goal
void Workspace::addRobotToGoal(Goal *goal, Robot *robot)
{
    // Check if the goal exists in the map
    if (_assignment.find(goal) != _assignment.end())
    {
        // Goal exists, so add the robot to its vector
        _assignment[goal].push_back(robot);
    }
    else
    {
        // Goal doesn't exist, create a new entry in the map
        std::vector<Robot *> robotList;
        robotList.push_back(robot);
        _assignment[goal] = robotList;
    }
}
*/