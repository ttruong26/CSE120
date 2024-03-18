#include "ExtractContent.h"

#include <utility>

using namespace std;

int ExtractContent::extractData(std::string fileName)
{
    string phrase = "DATA";

    vector<pair<int, int>> dataCoords;

    string line;
    ifstream mapFile(fileName);

    if (!mapFile.is_open())
    {
        std::cerr << "Failed to open the map file." << std::endl;
        return 0;
    }

    return 1;
}

Rect ExtractContent::extractBounds(std::string fileName)
{
    vector<pair<int, int>> boundCoordinates;
    for (int i = 0; i < 2; i++)
    {
        boundCoordinates.push_back(make_pair(0, 0));
    }

    string line;
    ifstream mapFile(fileName);

    if (!mapFile.is_open())
    {
        std::cerr << "Failed to open the map file." << std::endl;
        // add assert
    }

    while (getline(mapFile, line))
    {
        std::istringstream iss(line);
        std::string label;
        iss >> label;

        if (label == "MinPos:")
        {
            iss >> boundCoordinates[0].first >> boundCoordinates[0].second;
        }
        else if (label == "MaxPos:")
        {
            iss >> boundCoordinates[1].first >> boundCoordinates[1].second;
        }
    }

    mapFile.close();

    // GridInfo will hold the [width, height, topLeftXCoord, topLeftYCoord]
    Rect gridInfo;

    int width, height;
    width = boundCoordinates[1].first - boundCoordinates[0].first;
    height = boundCoordinates[1].second - boundCoordinates[0].second;
    gridInfo._width = (width);
    gridInfo._height = height;
    gridInfo._botLeftX = boundCoordinates[0].first;
    gridInfo._botLeftY = boundCoordinates[0].second;

    return gridInfo;
}

vector<Goal *> ExtractContent::extractGoals(std::string fileName)
{
    Tile *tile = NULL;
    vector<Goal *> goals;

    string line;
    ifstream mapFile(fileName);

    if (!mapFile.is_open())
    {
        std::cerr << "Failed to open the map file." << std::endl;
    }

    while (getline(mapFile, line))
    {
        std::istringstream iss(line);
        std::string token, cairnType, ignoredString, iconLabel, id;
        ;
        iss >> token;

        if (token == "Cairn:")
        {
            iss >> cairnType; // Read "GoalWithHeading"
            if (cairnType == "GoalWithHeading")
            {
                int x, y;
                double heading;
                std::string id;
                iss >> x >> y >> heading; // Read coordinates and heading
                iss >> ignoredString;     // Read and ignore the next token (should be empty quotes "")
                iss >> iconLabel;         // Read "ICON"
                if (iconLabel == "ICON")
                {
                    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"'); // Skip to the start of the ID (start quote)
                    std::getline(iss, id, '\"');                                   // Read the ID (up to the end quote)
                    Goal *goal = new Goal(x, y, heading, id);
                    goals.push_back(goal);
                }
            }
        }
    }

    mapFile.close();
    return goals;
}