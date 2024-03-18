#pragma once

#include "../TileGraph/TileGraph.h"
#include "../Objects/Goal.h"
#include "../static/MapLoader.h"

class Workspace
{
public:
    Workspace();
    void loadData();
    void print();
private:
    TileGraph* graph;
    std::vector<Goal *> goals;
    std::vector<Wall*> walls;
};