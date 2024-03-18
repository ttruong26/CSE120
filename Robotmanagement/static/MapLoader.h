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
    int extractData(std::string fileName);
    Rect extractBounds(std::string fileName); // Returns [width, height, topLeftXCoord, topLeftYCoord] as GridInfo
    std::vector<Goal *> extractGoals(std::string fileName);
    int extractLines(std::string fileName);
};