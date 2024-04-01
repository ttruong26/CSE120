#include "Workspace.h"

Workspace::Workspace()
{
    graph = new TileGraph();
}

void Workspace::loadData()
{
    MapLoader::LoadMap(*graph, goals, lines, "mapfiles/test.map");
}

void Workspace::printGoals()
{
    graph->print();
    for (int i = 0; i < goals.size(); i++)
    {
        goals[i]->print();
    }
    for (int i = 0; i < lines.size(); i++)
    {
        std::cout << "Line " << i << ": " << lines[i].x1 << ", " << lines[i].y1 << " to " << lines[i].x2 << ", " << lines[i].y2 << std::endl;
    }
}

void Workspace::placeLoadedGoals()
{
    for (int i = 0; i < goals.size(); i++)

    {
        graph->placeObject(goals[i]);
    }

    graph->getTileAt(-23540, -6326)->getObject()->print();
    if (graph->getTileAt(-23540, -6326)->isGoal() == true)
    {
        std::cout << "Goal placed at (-23540, -6326)" << std::endl;
    }

    if (graph->getTileAt(-23540, -6325)->isGoal() == true)
    {
        std::cout << "Goal placed at (-23540, -6325)" << std::endl;
    }
    else
    {
        std::cout << "Goal not placed at (-23540, -6325)" << std::endl;
    }
}

void Workspace:updateTable()
{
    // Iterate through each goal in the map
    for(auto& pair : goalRobotMap) {
        Goal* goal = pair.first;
        std::vector<Robot*>& robots = pair.second;

        // Calculate distance of each robot from the goal
        std::sort(robots.begin(), robots.end(), [goal](Robot* a, Robot* b) {
            return a->distanceToGoal(goal) < b->distanceToGoal(goal); // Note distanceToGoal() should be replaced with the method that returns the time
                                                                      // from robot to destination.
        });
    }

    std::cout << "Table updated." << std::endl;
}

void Workspace::addRobotToGoal(Goal* goal, Robot* robot)
{
    // Check if the goal exists in the map
    if(goalRobotMap.find(goal) != goalRobotMap.end())
    {
        // Goal exists, so add the robot to its vector
        goalRobotMap[goal].push_back(robot);
    }
    else
    {
        // Goal doesn't exist, create a new entry in the map
        std::vector<Robot*> robotList;
        robotList.push_back(robot);
        goalRobotMap[goal] = robotList;
    }
}
