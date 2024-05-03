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
    mGraph->print();
    std::cout << std::endl;

    this->placeLoadedGoals();
    this->placeLoadedObstacles();
    this->createRobots();

    // Once robots are and goals are loaded and placed on graph, we can create the assignment map
    this->createAssignmentMap();
}

void Workspace::createRobots()
{
    // Create robots. For now, we will create two robots.
    robot1 = new Robot(-2610, -1995, 1, 120);
    mGraph->placeObject(robot1);
    robot2 = new Robot(-2609, -486, 2, 120);
    mGraph->placeObject(robot2);
}

void Workspace::createAssignmentMap()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        _assignment[_goals[i]] = std::vector<Robot *>();
    }

    // We will assign every robot to every goal, to find the predicted time for each robot and find the best fit
    for (int i = 0; i < _goals.size(); i++)
    {
        _assignment[_goals[i]].push_back(robot1);
        _assignment[_goals[i]].push_back(robot2);
    }
}

void Workspace::printGoals()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        _goals[i]->print();
    }

    /*
    // Test the predictTimeEstimation function for both Robots
    double distance = robot1->predictTimeEstimation(_goals[0]);
    std::cout << "Time Prediction: " << distance << std::endl;
    double distance2 = robot2->predictTimeEstimation(_goals[0]);
    std::cout << "Time Prediction: " << distance2 << std::endl;
    */
}

void Workspace::printAssignmentTable()
{
    // Print the assignment table
    for (auto &pair : _assignment)
    {
        std::shared_ptr<Goal> goal = pair.first;
        std::vector<Robot *> &robots = pair.second;
        std::cout << goal->getGoalId() << " | ";

        for (int i = 0; i < robots.size(); i++)
        {
            robots[i]->print();
            std::cout << ", ";
        }
        std::cout << "|" << std::endl;
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

    // mGraph->getTileAt(-15840, -11900)->getObject()->print();
    /*
    if (graph->getTileAt(-15840, -11900)->isWall() == true)
    {
        std::cout << "Wall placed at (-15840, -11900)";
    }
    else
    {
        std::cout << "Wall not placed at (-15840, -11900)";
    }
    */

    /* Test
    graph->getTileAt(-25582, -12574)->getObject()->print();
    graph->getTileAt(-25582, -12575)->Print();

    if (graph->getTileAt(-25582, -12574)->isWall() == true)
    {
        std::cout << "Wall placed at (-25582, -12574)";
    }
    else
    {
        std::cout << "Wall not placed at (-25582, -12574)";
    }
    */
}

void Workspace::placeLoadedGoals()
{
    for (int i = 0; i < _goals.size(); i++)

    {
        mGraph->placeObject(_goals[i].get());
    }

    /*
    graph->getTileAt(-23540, -6326)->getObject()->print();
    if (graph->getTileAt(-23540, -6326)->isGoal() == true)
    {
        std::cout << "Goal placed at (-23540, -6326)";
    }

    if (graph->getTileAt(-23540, -6325)->isGoal() == true)
    {
        std::cout << "Goal placed at (-23540, -6325)";
    }
    else
    {
        std::cout << "Goal not placed at (-23540, -6325)";
    }
    */
}

void Workspace::cleanUp()
{
    delete mGraph;
    delete robot1;
    delete robot2;
}

void Workspace::updateTable()
{

    // Iterate through each goal in the map
    for (auto &pair : _assignment)
    {
        std::shared_ptr<Goal> goal = pair.first;
        std::vector<Robot *> &robots = pair.second;
        std::cout << std::endl;

        // Calculate distance of each robot from the goal
        std::sort(robots.begin(), robots.end(), [goal](Robot *a, Robot *b)
                  {
                      return a->predictTimeEstimation(goal) < b->predictTimeEstimation(goal);
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