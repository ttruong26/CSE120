#pragma once

#include "../TileGraph/TileGraph.h"
#include "../Objects/Goal.h"
#include "../Objects/Wall.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

class MapLoader
{
public:
    static void LoadMap(TileGraph &graph, std::vector<Goal *> &goals, std::vector<Wall *> &walls, std::string fileName);

private:
};