#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

#include "../Utility.h"
#include "../Objects/Goal.h"
#include "../TileGraph/TileGraph.h"
#include "../Objects/Wall.h"

class ExtractContent
{
public:
    static int extractData(std::string fileName);
    static Rect extractBounds(std::string fileName); // Returns [width, height, topLeftXCoord, topLeftYCoord] as GridInfo
    static std::vector<Goal *> extractGoals(std::string fileName);
    static int extractLines(std::string fileName);
};