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