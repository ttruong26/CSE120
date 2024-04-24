#include "MapLoader.h"

using namespace std;

void MapLoader::LoadMap(TileGraph &graph, std::vector<std::unique_ptr<Goal>> &goals, std::vector<std::unique_ptr<Line>> &lines, std::vector<std::unique_ptr<Data>> &dataPoints, std::string fileName)
{
    vector<Point> boundCoordinates;

    string line;
    bool isProcessingLines = false;
    bool isProcessingData = false;
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
                // Goal *goal;
                double heading;
                std::string id;
                iss >> _x >> _y >> heading; // Read coordinates and heading
                iss >> ignoredString;       // Read and ignore the next token (should be empty quotes "")
                iss >> iconLabel;           // Read "ICON"
                if (iconLabel == "ICON")
                {
                    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"'); // Skip to the start of the ID (start quote)
                    std::getline(iss, id, '\"');                                   // Read the ID (up to the end quote)
                    // goal = new Goal(_x, _y, heading, id);
                    goals.push_back(make_unique<Goal>(_x, _y, heading, id));
                    // goals.push_back(goal);
                }
            }
        }

        if (line == "LINES")
        {
            isProcessingLines = true; // Found the "LINES" section
            continue;                 // Skip processing this line and move to the next line
        }
        else if (line == "DATA")
        {
            isProcessingData = true;
            isProcessingLines = false;
            continue;
        }
        if (isProcessingLines)
        {
            if (line.empty() || isalpha(line[0]))
            {
                isProcessingLines = false;
                break;
            }

            std::istringstream iss(line);
            Line *l = new Line();
            int x1, y1, x2, y2;
            // Extract coordinates from the line and store them in the 'Line' struct
            if (iss >> x1 >> y1 >> x2 >> y2)
            {
                // l->setEndPoints(x1, y1, x2, y2);
                lines.push_back(make_unique<Line>(x1, y1, x2, y2));
                // lines.push_back(l);
            }
            else
            {
                std::cerr << "Failed to parse line: " << line << std::endl;
            }
        }

        // Process the points under the DATA section in the map file
        if (isProcessingData)
        {
            if (line.empty() || isalpha(line[0]))
            {
                isProcessingData = false; // Stop processing data if an empty line or a new section is encountered
                continue;
            }
            std::istringstream iss(line);
            // Data *d = new Data();
            int x, y;
            if (iss >> x >> y)
            {
                // d->setPosition(x, y);
                // points.push_back(d);
                dataPoints.push_back(make_unique<Data>(x, y));
            }
            else
            {
                std::cerr << "Failed to parse data point: " << line << std::endl;
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

void MapLoader::LoadWorkspace(const std::string &fileName, TileGraph &graph, std::vector<Goal *> &goals, std::vector<Line *> &lines, std::vector<Data *> &points)
{
    std::ifstream mapFile(fileName);
    if (!mapFile.is_open())
    {
        std::cerr << "Failed to open the map file." << std::endl;
        return;
    }

    loadBoundaries(mapFile, graph);
    loadGoals(mapFile, goals);
    loadLines(mapFile, lines);
    loadDataPoints(mapFile, points);
}

void MapLoader::loadBoundaries(std::ifstream &mapFile, TileGraph &graph)
{
    std::string line;
    std::vector<Point> boundCoordinates;
    while (std::getline(mapFile, line) && !line.empty())
    {
        std::istringstream iss(line);
        std::string label;
        int x, y;
        iss >> label;
        if (label == "MinPos:" || label == "MaxPos:")
        {
            iss >> x >> y;
            boundCoordinates.push_back(Point(x, y));
        }
    }
    // Assume boundaries are loaded properly
    // Calculate and set the bounds of the graph from the coordinates
    Rect gridInfo;

    gridInfo._width = boundCoordinates[1]._x - boundCoordinates[0]._x;
    gridInfo._height = boundCoordinates[1]._y - boundCoordinates[0]._y;
    gridInfo._botLeftX = boundCoordinates[0]._x;
    gridInfo._botLeftY = boundCoordinates[0]._y;

    graph.setBounds(gridInfo._width, gridInfo._height, gridInfo._botLeftX, gridInfo._botLeftY);
}

void MapLoader::loadGoals(std::ifstream &mapFile, std::vector<Goal *> &goals)
{
    std::string line;
    while (std::getline(mapFile, line) && !line.empty())
    {
        std::istringstream iss(line);
        std::string label, cairnType, ignoredString, iconLabel;
        if (label == "Cairn:")
        {
            iss >> cairnType;
            if (cairnType == "GoalWithHeading")
            {
                int x, y;
                double heading;
                std::string id;
                iss >> x >> y >> heading;
                iss >> ignoredString; // Read and ignore the next token (should be empty quotes "")
                iss >> iconLabel;     // Read "ICON"
                if (iconLabel == "ICON")
                {
                    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\"'); // Skip to the start of the ID (start quote)
                    std::getline(iss, id, '\"');                                   // Read the ID (up to the end quote)
                    goals.push_back(new Goal(x, y, heading, id));
                }
            }
        }
    }
}

void MapLoader::loadLines(std::ifstream &mapFile, std::vector<Line *> &lines)
{
    std::string line;
    bool isProcessingLines = false;
    while (std::getline(mapFile, line) && !line.empty())
    {
        std::istringstream iss(line);

        if (line == "LINES")
        {
            isProcessingLines = true; // Found the "LINES" section
            continue;                 // Skip processing this line and move to the next line
        }

        if (isProcessingLines)
        {
            if (line.empty() || isalpha(line[0]))
            {
                isProcessingLines = false;
                break;
            }

            int x1, y1, x2, y2;
            if (iss >> x1 >> y1 >> x2 >> y2)
            {
                lines.push_back(new Line(x1, y1, x2, y2));
            }
        }
    }
}

void MapLoader::loadDataPoints(std::ifstream &mapFile, std::vector<Data *> &points)
{
    std::string line;
    bool isProcessingData = false;
    while (std::getline(mapFile, line) && !line.empty())
    {
        std::istringstream iss(line);
        if (line == "DATA")
        {
            isProcessingData = true;
            continue;
        }

        if (isProcessingData)
        {
            if (line.empty() || isalpha(line[0]))
            {
                isProcessingData = false; // Stop processing data if an empty line or a new section is encountered
                continue;
            }

            int x, y;
            if (iss >> x >> y)
            {
                points.push_back(new Data(x, y));
            }
        }
    }
}