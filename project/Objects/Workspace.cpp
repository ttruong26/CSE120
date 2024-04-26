#include "Workspace.h"

Workspace::Workspace()
{
    mGraph = new TileGraph();
}

void Workspace::loadData()
{
    // Load tile Graph
    MapLoader::LoadMap(*mGraph, _goals, _lines, _dataPoints, "mapfiles/test.map");
    MapObject::_graph = mGraph;
    mGraph->print();
    for (int i = 0; i < _goals.size(); i++)
    {
        _goals[i]->print();
    }

    this->placeLoadedGoals();
    this->placeLoadedObstacles();

    // Create and place robots
    robot1 = new Robot(-26100, -19959, 0, 1200);
    mGraph->placeObject(robot1);
    robot2 = new Robot(-26099, -4861, 0, 1200);
    mGraph->placeObject(robot2);

    // Once robots are and goals are loaded and placed on graph, we can create the assignment map
    this->createAssignmentMap();
}

void Workspace::createAssignmentMap()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        _assignment[_goals[i].get()] = std::vector<Robot *>();
    }

    // We will assign every robot to every goal, to find the predicted time for each robot and find the best fit
    for (int i = 0; i < _goals.size(); i++)
    {
        _assignment[_goals[i].get()].push_back(robot1);
        _assignment[_goals[i].get()].push_back(robot2);
    }
}

void Workspace::printGoals()
{
    for (int i = 0; i < _goals.size(); i++)
    {
        _goals[i]->print();
    }

    double distance = robot1->predictTimeEstimation(_goals[0]);
    std::cout << "Time Prediction: " << distance << std::endl;
    double distance2 = robot2->predictTimeEstimation(_goals[0]);
    std::cout << "Time Prediction: " << distance2 << std::endl;

    for (auto &pair : _assignment)
    {
        Goal *goal = pair.first;
        std::vector<Robot *> &robots = pair.second;

        for (int i = 0; i < robots.size(); i++)
        {
            std::cout << "Robot " << i << " assigned to goal: ";
            goal->print();
        }
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

    if (graph->getTileAt(-25582, -12575)->isWall() == true)
    {
        std::cout << "Wall placed at (-25582, -12575)";
    }
    else
    {
        std::cout << "Wall not placed at ( -25582, -12575)";
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
    /*
    // Iterate through each goal in the map
    for (auto &pair : _assignment)
    {
        Goal *goal = pair.first;
        std::vector<Robot *> &robots = pair.second;

        // Calculate distance of each robot from the goal
        std::sort(robots.begin(), robots.end(), [goal](Robot *a, Robot *b)
                  {
                      return a->preditctTimeEstimation(goal) < b->preditctTimeEstimation(goal);
                      //  from robot to destination.
                  });
    }

    std::cout << "Table updated." << std::endl;
    */
}

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