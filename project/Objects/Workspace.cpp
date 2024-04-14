#include "Workspace.h"

Workspace::Workspace()
{
    mGraph = new TileGraph();
}

void Workspace::loadData()
{
    MapLoader::LoadMap(*mGraph, goals, lines, dataPoints, "mapfiles/test.map");
    MapObject::_graph = mGraph;
    robot1 = new Robot(-26099, -19959, 0);
    // mGraph->placeObject(robot1);
}

void Workspace::printGoals()
{
    // graph->print();
    for (int i = 0; i < goals.size(); i++)
    {
        goals[i]->print();
    }
}

void Workspace::placeLoadedObstacles()
{

    for (int i = 0; i < lines.size(); i++)
    {
        if (i == 17) // The 17th line is out of bounds of the workspace
        {
            continue;
        }
        mGraph->placeObject(lines[i]);
    }

    for (int i = 0; i < dataPoints.size(); i++)
    {
        mGraph->placeObject(dataPoints[i]);
    }

    mGraph->getTileAt(-15840, -11900)->getObject()->print();
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
    for (int i = 0; i < goals.size(); i++)

    {
        mGraph->placeObject(goals[i]);
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

void Workspace::updateTable()
{
    /*
    // Iterate through each goal in the map
    for (auto &pair : goalRobotMap)
    {
        Goal *goal = pair.first;
        std::vector<Robot *> &robots = pair.second;

        // Calculate distance of each robot from the goal
        std::sort(robots.begin(), robots.end(), [goal](Robot *a, Robot *b)
                  {
                      // return a->distanceToGoal(goal) < b->distanceToGoal(goal); // Note distanceToGoal() should be replaced with the method that returns the time
                      //  from robot to destination.
                  });
    }

    std::cout << "Table updated." << std::endl;
    */
}

void Workspace::addRobotToGoal(Goal *goal, Robot *robot)
{
    // Check if the goal exists in the map
    if (goalRobotMap.find(goal) != goalRobotMap.end())
    {
        // Goal exists, so add the robot to its vector
        goalRobotMap[goal].push_back(robot);
    }
    else
    {
        // Goal doesn't exist, create a new entry in the map
        std::vector<Robot *> robotList;
        robotList.push_back(robot);
        goalRobotMap[goal] = robotList;
    }
}