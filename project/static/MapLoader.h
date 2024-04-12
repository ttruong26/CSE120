#pragma once

#include "../TileGraph/TileGraph.h"
#include "../Objects/Goal.h"
#include "../Objects/Line.h"
#include "../Objects/Data.h"
#include "../Utility.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

class MapLoader
{
public:
    static void LoadMap(TileGraph &graph, std::vector<Goal *> &goals, std::vector<Line *> &lines, std::vector<Data *> &points, std::string fileName);

private:
};