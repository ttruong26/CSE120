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

    // Once robots are and goals are loaded and placed on graph, we can create the assignment map
}

// Test function to create robots
std::vector<Robot *> Workspace::createRobots(int num)
{
    int x = _origin._x;
    int y = _origin._y;
    for (int i = 0; i < num; i++)
    {
        Robot *robot = new Robot(x, y, i, 1200);
        mGraph->placeObject(robot);
        _robots.push_back(robot);
        x += 50;
        y += 50;
    }

    this->createAssignmentTable();
    this->sortAssignmentTable();

    return _robots;
}

void Workspace::addRobot(Robot *robot)
{
    _robots.push_back(robot);
    if (_assignment.size() == 0)
        this->createAssignmentTable();
    else
    {
        for (int i = 0; i < _goals.size(); i++)
        {
            std::string goalName = _goals[i]->getGoalId();
            RobotGoalPrediction prediction;
            prediction._robot = robot;
            prediction._time = robot->predictTimeEstimation(_goals[i]);
            _assignment[goalName].push_back(prediction);
        }
    }
    this->sortAssignmentTable();
}

void Workspace::createAssignmentTable()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        std::string goalName = _goals[i]->getGoalId();
        _assignment[goalName] = std::vector<RobotGoalPrediction>();
        _goalsMap[goalName] = _goals[i];
    }

    // We will assign every robot to every goal, to find the predicted time for each robot and find the best fit
    for (int i = 0; i < _goals.size(); i++)
    {
        for (auto robot : _robots)
        {
            RobotGoalPrediction prediction;
            prediction._robot = robot;
            prediction._time = robot->predictTimeEstimation(_goals[i]);
            _assignment[_goals[i]->getGoalId()].push_back(prediction);
        }
    }
}

void Workspace::updateAssignmentTable()
{
    for (auto &pair : _assignment)
    {
        std::string goal = pair.first;
        auto &robotPredictionList = pair.second;
        for (auto &robotPrediction : robotPredictionList)
        {
            robotPrediction._time = robotPrediction._robot->predictTimeEstimation(_goalsMap[goal]);
        }
    }
    this->sortAssignmentTable();
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
        std::cout << goalName << " | ";
        for (auto container : pair.second)
        {
            Robot *robot = container._robot;
            robot->print();
            std::cout << " " << container._time << " | ";
        }
        std::cout << std::endl;
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
        // Search for the goal in the assignment table
        if (pair.first == goalId)
        {
            for (auto robotPredictionList : pair.second)
            {
                Robot *robot = robotPredictionList._robot;
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
    else
    {
        std::cout << "No robot available for goal " << goalId << std::endl;
    }
}

void Workspace::setRobotWorking(Robot *robot)
{
    std::string bestGoal;
    double bestTime = 1000000;
    for (const auto &pair : _assignment)
    {
        std::string goal = pair.first;
        if (_goalsMap[goal]->isWorking() == true)
        {
            continue;
        }
        auto &robotPredictionList = pair.second;
        // Check if the given robot is the assigned robot for the goal
        if (robot->getId() == getAssignedRobot(goal)->getId())
        {
            for (auto robotPredictionList : pair.second)
                if (robotPredictionList._robot->getId() == robot->getId() && robotPredictionList._time < bestTime)
                {
                    bestTime = robotPredictionList._time;
                    bestGoal = goal;
                }
        }
    }
    std::cout << "Robot " << robot->getId() << " is set to work on " << bestGoal << std::endl;
    robot->assignTask(_goalsMap[bestGoal]);
    _goalsMap[bestGoal]->setWorking(true);
}

void Workspace::setAllRobotsWorking()
{
    for (auto &pair : _assignment)
    {
        Robot *robot = getAssignedRobot(pair.first);
        this->setRobotWorking(robot);
    }
    /*
    for (auto &robot : _robots)
    {
        // this->setRobotWorking(robot);
        //  assignRobotToGoal(pair.first);
    }
    */
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
}

void Workspace::sortAssignmentTable()
{

    // Iterate through each goal in the map
    for (auto &pair : _assignment)
    {
        std::string goal = pair.first;
        auto &robotPredictionList = pair.second;

        // Calculate distance of each robot from the goal
        // Calculate distance of each robot from the goal
        std::sort(robotPredictionList.begin(), robotPredictionList.end(), [this, goal](const RobotGoalPrediction &a, const RobotGoalPrediction &b)
                  {
                    auto goalIter = _goalsMap.find(goal);
                    if (goalIter != _goalsMap.end())
                        return a._time < b._time;
                    else
                          std::cout << "Goal not found in goal map" << std::endl;
                      return true;
                    

                    /*
                      auto goalIter = _goalsMap.find(goal);
                      if (goalIter != _goalsMap.end())
                          return a->predictTimeEstimation(goalIter->second) < b->predictTimeEstimation(goalIter->second);
                      else
                          std::cout << "Goal not found in goal map" << std::endl;
                      return true;
                      */ });
        // Assign the robot with the shortest predicted time to the goal
        // robot[0]->assign(goal);
    }

    std::cout << std::endl
              << "Robots assigned to goals." << std::endl;
}

Robot *Workspace::getRobot(int id)
{
    for (auto robot : _robots)
    {
        if (robot->getId() == id)
        {
            return robot;
        }
    }
    return NULL;
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