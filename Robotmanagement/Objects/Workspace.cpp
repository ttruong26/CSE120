#include "Workspace.h"

Workspace::Workspace()
{
    graph = new TileGraph();
}

void Workspace::loadData()
{
    MapLoader::LoadMap(*graph, goals, walls, "mapfiles/test.map");
}

void Workspace::print()
{
    graph->print();
    for (int i = 0; i < goals.size(); i++)
    {
        goals[i]->print();
    }
}