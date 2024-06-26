#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>

using namespace std;

// Define a structure for a node in the grid
struct Node
{
    int x, y;
    double f, g, h;
    int directionChange; // Number of direction changes from start to this node
    Node *parent;

    Node(int _x, int _y, double _f, double _g, double _h, int _directionChange = 0, Node *_parent = nullptr)
        : x(_x), y(_y), f(_f), g(_g), h(_h), directionChange(_directionChange), parent(_parent) {}

    bool operator>(const Node &other) const
    {
        return f > other.f;
    }
};

// Function to calculate distance between two points
double calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1) * 100, 2) + pow((y2 - y1) * 100, 2)); // Convert back to millimeters for accurate distance calculation
}

// Function to check if a point lies within an obstacle area
bool isInObstacle(int x, int y, const vector<pair<int, int>> &obstacles)
{
    for (const auto &obstacle : obstacles)
    {
        if (x == obstacle.first && y >= obstacle.second)
        {
            return true;
        }
    }
    return false;
}

// Function to check if a point lies on a line segment
bool isOnLineSegment(int x, int y, int x1, int y1, int x2, int y2)
{
    // Check if the point lies within the bounding box of the line segment
    if ((x >= min(x1, x2) && x <= max(x1, x2)) && (y >= min(y1, y2) && y <= max(y1, y2)))
    {
        // Calculate the cross product to determine if the point lies on the line
        int crossProduct = (y2 - y1) * (x - x1) - (x2 - x1) * (y - y1);
        if (crossProduct == 0) // Point lies on the line
            return true;
    }
    return false;
}

bool isInObstacle(int x, int y, const vector<pair<int, int>> &obstacles, const vector<pair<int, int>> &lineSegments)
{
    for (const auto &obstacle : obstacles)
    {
        if (x == obstacle.first && y >= obstacle.second)
        {
            return true;
        }
    }
    for (const auto &segment : lineSegments)
    {
        if (isOnLineSegment(x, y, segment.first, segment.second, segment.first + 1, segment.second + 1))
        {
            return true;
        }
    }
    return false;
}

// Modify A* search to incorporate collision checking with line segments and turning time
double performAStar(int startX, int startY, int goalX, int goalY, double averageSpeed,
                    const vector<pair<int, int>> &obstacles, const vector<pair<int, int>> &lineSegments,
                    int gridSizeX, int gridSizeY)
{
    // Initialize priority queue and visited array
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    vector<vector<bool>> visited(gridSizeX, vector<bool>(gridSizeY, false));

    // Push the starting node onto the open set
    openSet.push(Node(startX, startY, 0, 0, calculateDistance(startX, startY, goalX, goalY)));

    // A* search loop
    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        // Check if goal reached
        if (current.x == goalX && current.y == goalY)
        {
            return (current.g + current.directionChange * 0.5) / averageSpeed; // Return time to reach goal including turning time
        }

        // Check if node is already visited or in an obstacle
        if (visited[current.x][current.y] || isInObstacle(current.x, current.y, obstacles, lineSegments))
        {
            continue; // Skip this node
        }

        // Mark node as visited
        visited[current.x][current.y] = true;

        // Iterate over neighbor nodes
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int nextX = current.x + dx;
                int nextY = current.y + dy;

                // Check if neighbor node is within grid bounds
                if (nextX < 0 || nextX >= gridSizeX || nextY < 0 || nextY >= gridSizeY)
                {
                    continue;
                }

                // Calculate new cost to reach neighbor node
                double newCost = current.g + calculateDistance(current.x, current.y, nextX, nextY);

                // Calculate additional time for turning
                int turningTime = 0;
                if ((dx != 0 && dy == 0) || (dx == 0 && dy != 0))
                {
                    if ((current.parent != nullptr) && (dx != current.x - current.parent->x || dy != current.y - current.parent->y))
                    {
                        turningTime = 0.5;
                    }
                }

                // Add turning time to the new costa
                newCost += turningTime;

                // Check if neighbor node is not visited and not in an obstacle
                if (!visited[nextX][nextY] && !isInObstacle(nextX, nextY, obstacles, lineSegments))
                {
                    // Calculate heuristic cost (distance to goal)
                    double heuristic = calculateDistance(nextX, nextY, goalX, goalY);
                    double f = newCost + heuristic; // Total estimated cost

                    // Push neighbor node onto open set
                    openSet.push(Node(nextX, nextY, f, newCost, heuristic, current.directionChange + turningTime, &current));
                }
            }
        }
    }

    return -1; // Path not found
}

int main()
{
    int minPosX = -45000;
    int minPosY = -18000;
    int maxPosX = -10000;
    int maxPosY = -5000;
    double averageSpeed = 1200; // in mm/sec

    // Define obstacle areas
    vector<pair<int, int>> obstacles = {
        {-26100, -18640}, {-26100, -18540}, {-26100, -18520}, {-26100, -18440}, {-26100, -18400}, {-26100, -18360}, {-26100, -18340}, {-26100, -18320}, {-26100, -18300}, {-26100, -18280}, {-26100, -18140}, {-26100, -18120}, {-26100, -15700}, {-26080, -18580}, {-26080, -18400}, {-26080, -18160}, {-26080, -18140}, {-26080, -15680}, {-26080, -11960}, {-26060, -18560}, {-26060, -18140}, {-26060, -15680}, {-26040, -18680}, {-26040, -18560}, {-26040, -18200}, {-26040, -18160}, {-26040, -18140}, {-26020, -18600}, {-26020, -18580}, {-26020, -18160}, {-26020, -15700}, {-26020, -15680}, {-26000, -18680}, {-26000, -18660}, {-26000, -18160}, {-26000, -11120}, {-25980, -18680}, {-25980, -18480}, {-25980, -18440}, {-25980, -18160}, {-25980, -18120}, {-25980, -18100}, {-25980, -15720}, {-25980, -15680}, {-25980, -13620}, {-25980, -10100}, {-25980, -10060}, {-25980, -10040}, {-25960, -18660}, {-25960, -18580}, {-25960, -18460}, {-25960, -18440}, {-25960, -18160}, {-25960, -18120}, {-25960, -13640}, {-25960, -10020}, {-25940, -18500}, {-25940, -18140}, {-25940, -15700}, {-25940, -15680}, {-25940, -13600},
        // Add obstacle coordinates here
    };

    // Define line segments
    vector<pair<int, int>> lineSegments = {
        {-25582, -12574}, {-25581, -13468}, {-25490, -13950}, {-25489, -14764}, {-25473, -14920}, {-25472, -16072}, {-25472, -16072}, {-25471, -17360}, {-25452, -5705}, {-25451, -6452}, {-25387, -17360}, {-25385, -19792}, {-25385, -12062}, {-25383, -14193}, {-25374, -14193}, {-25373, -14920}, {-25374, -6452}, {-25372, -7681}, {-25365, -7681}, {-25360, -11770}, {-25201, -19804}, {-23558, -19802}, {-24844, -15684}, {-23692, -15682}, {-23692, -15837}, {-24844, -15839}, {-23558, -19831}, {-24197, -19831}, {-21802, -19826}, {-16128, -19819}, {-21757, -19938}, {-21802, -19826}, {-21488, -19815}, {-21757, -19938}, {-21487, -19980}, {-21488, -19815}, {-19609, -19838}, {-20818, -19840}, {-18297, -18630}, {-18259, -18332}, {-18282, -18330}, {-18282, -17668}, {-17299, -6850}, {-17300, -5279}, {-16649, -17210}, {-16650, -16578}, {-16301, -6849}, {-17299, -6850}, {-16277, -17675}, {-16277, -17241}, {-16255, -16578}, {-16256, -16049}, {-16120, -13555}, {-16121, -12442}, {-16012, -19932}, {-16015, -17111}, {-15996, -4933}, {-25421, -4944}, {-15989, -17241}, {-16001, -6277}, {-15854, -12120}, {-15855, -11586}
        // Add line segment coordinates here
    };

    // Calculate grid size
    int gridSizeX = abs(maxPosX - minPosX) / 100 + 1;
    int gridSizeY = abs(maxPosY - minPosY) / 100 + 1;

    cout << "Starting A* search..." << endl;

    double timeRemaining = performAStar((minPosX + abs(minPosX)) / 100, (minPosY + abs(minPosY)) / 100,
                                        (maxPosX + abs(minPosX)) / 100, (maxPosY + abs(minPosY)) / 100,
                                        averageSpeed, obstacles, lineSegments, gridSizeX, gridSizeY);

    if (timeRemaining >= 0)
    {
        cout << "Estimated time remaining: " << timeRemaining << " seconds" << endl;
        cout << "Estimated distance remaining: " << timeRemaining * averageSpeed / 1000 << " meters" << endl;
    }
    else
    {
        cout << "Path not found!" << endl;
    }

    return 0;
}