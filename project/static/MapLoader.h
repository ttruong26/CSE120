#pragma once

#include "../graph/TileGraph.h"
#include "../Objects/Goal.h"
#include "../Objects/Line.h"
#include "../Objects/Data.h"
#include "../include/Utility.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <memory>

class MapLoader
{
public:
    static void LoadMap(TileGraph &graph, std::vector<std::shared_ptr<Goal>> &goals, std::vector<std::shared_ptr<Line>> &lines, std::vector<std::shared_ptr<Data>> &dataPoints, std::string fileName);

    static void LoadWorkspace(const std::string &fileName, TileGraph &graph, std::vector<Goal *> &goals, std::vector<Line *> &lines, std::vector<Data *> &points);

private:
    static void loadBoundaries(std::ifstream &mapFile, TileGraph &graph);
    static void loadGoals(std::ifstream &mapFile, std::vector<Goal *> &goals);
    static void loadLines(std::ifstream &mapFile, std::vector<Line *> &lines);
    static void loadDataPoints(std::ifstream &mapFile, std::vector<Data *> &points);
};