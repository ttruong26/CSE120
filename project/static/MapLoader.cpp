#include "MapLoader.h"

using namespace std;

void MapLoader::LoadMap(TileGraph &graph, std::vector<Goal *> &goals, std::vector<Line *> &lines, std::string fileName)
{
    Tile *tile = NULL;
    vector<Point> boundCoordinates;

    string line;
    bool isInLinesSection = false;
    ifstream mapFile(fileName);

    if (!mapFile.is_open())
    {
        std::cerr << "Failed to open the map file." << std::endl;
    }

    while (getline(mapFile, line))
    {
        std::istringstream iss(line);
        std::string label, cairnType, ignoredString, iconLabel, id;
        int x, y;
        iss >> label;

        if (line == "LINES")
        {
            isInLinesSection = true; // Found the "LINES" section
            continue;                // Skip processing this line and move to the next line
        }

        if (isInLinesSection)
        {
            if (line.empty() || isalpha(line[0]))
            {
                // If a new section is encountered or an empty line, end the loop
                break;
            }

            std::istringstream iss(line);
            Line *l = new Line();
            int x1, y1, x2, y2;
            // Extract coordinates from the line and store them in the 'Line' struct
            if (iss >> x1 >> y1 >> x2 >> y2)
            {
                l->setEndPoints(x1, y1, x2, y2);
                lines.push_back(l);
            }
            else
            {
                std::cerr << "Failed to parse line: " << line << std::endl;
            }
        }

        if (label == "MinPos:")
        {
            iss >> x >> y;
            Point p(x, y);
            boundCoordinates.push_back(p);
        }
        else if (label == "MaxPos:")
        {
            iss >> x >> y;
            Point p(x, y);
            boundCoordinates.push_back(p);
        }

        else if (label == "Cairn:")
        {
            iss >> cairnType; // Read "GoalWithHeading"
            if (cairnType == "GoalWithHeading")
            {
                int _x, _y;
                Goal *goal;
                double heading;
                std::string id;
                iss >> _x >> _y >> heading; // Read coordinates and heading
                iss >> ignoredString;       // Read and ignore the next token (should be empty quotes "")
                iss >> iconLabel;           // Read "ICON"
                if (iconLabel == "ICON")
                {
                    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"'); // Skip to the start of the ID (start quote)
                    std::getline(iss, id, '\"');                                   // Read the ID (up to the end quote)
                    goal = new Goal(_x, _y, heading, id);
                    goals.push_back(goal);
                }
            }
        }
    }
    mapFile.close();

    // GridInfo will hold the [width, height, topLeftXCoord, topLeftYCoord]
    Rect gridInfo;

    gridInfo._width = boundCoordinates[1]._x - boundCoordinates[0]._x;
    gridInfo._height = boundCoordinates[1]._y - boundCoordinates[0]._y;
    gridInfo._botLeftX = boundCoordinates[0]._x;
    gridInfo._botLeftY = boundCoordinates[0]._y;

    graph.setBounds(gridInfo._width, gridInfo._height, gridInfo._botLeftX, gridInfo._botLeftY); // Set tileGraph with extracted bounds
}