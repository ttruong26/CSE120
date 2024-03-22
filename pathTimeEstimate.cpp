#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>

using namespace std;

// Define a structure for a node in the grid
struct Node {
    int x, y;
    double f, g, h;
    Node* parent;

    Node(int _x, int _y, double _f, double _g, double _h, Node* _parent = nullptr)
        : x(_x), y(_y), f(_f), g(_g), h(_h), parent(_parent) {}

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// Function to calculate distance between two points
double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow((x2 - x1) * 100, 2) + pow((y2 - y1) * 100, 2)); // Convert back to millimeters for accurate distance calculation
}

// Function to check if a point lies within an obstacle area
bool isInObstacle(int x, int y, const vector<pair<int, int>>& obstacles) {
    for (const auto& obstacle : obstacles) {
        if (x == obstacle.first && y >= obstacle.second) {
            return true;
        }
    }
    return false;
}

// Function to perform A* search
double performAStar(int startX, int startY, int goalX, int goalY, double averageSpeed, const vector<pair<int, int> >& obstacles, int gridSizeX, int gridSizeY) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    vector<vector<bool> > visited(gridSizeX, vector<bool>(gridSizeY, false));

    openSet.push(Node(startX, startY, 0, 0, calculateDistance(startX, startY, goalX, goalY)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == goalX && current.y == goalY) {
            return current.g / averageSpeed;
        }

        if (visited[current.x][current.y] || isInObstacle(current.x, current.y, obstacles)) {
            continue;
        }

        visited[current.x][current.y] = true;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                int nextX = current.x + dx;
                int nextY = current.y + dy;

                if (nextX < 0 || nextX >= gridSizeX || nextY < 0 || nextY >= gridSizeY) {
                    continue;
                }

                double newCost = current.g + calculateDistance(current.x, current.y, nextX, nextY);

                if (!visited[nextX][nextY] && !isInObstacle(nextX, nextY, obstacles)) {
                    double heuristic = calculateDistance(nextX, nextY, goalX, goalY);
                    double f = newCost + heuristic;

                    openSet.push(Node(nextX, nextY, f, newCost, heuristic));
                }
            }
        }
    }

    return -1; // Path not found
}

int main() {
    int minPosX = -29200;
    int minPosY = -19930;
    int maxPosX = -10940;
    int maxPosY = -4280;
    double averageSpeed = 1200; // in mm/sec

    // Define obstacle areas
    vector<pair<int, int> > obstacles;
     obstacles.push_back(make_pair(-26100, -18640));
     obstacles.push_back(make_pair(-26100, -18540));
     obstacles.push_back(make_pair(-26100, -18520));
     obstacles.push_back(make_pair(-26100, -18440));
     obstacles.push_back(make_pair(-26100, -18400));
     obstacles.push_back(make_pair(-26100, -18360));
     obstacles.push_back(make_pair(-26100, -18340));
     obstacles.push_back(make_pair(-26100, -18320));
     obstacles.push_back(make_pair(-26100, -18300));
     obstacles.push_back(make_pair(-26100, -18280));
     obstacles.push_back(make_pair(-26100, -18140));
     obstacles.push_back(make_pair(-26100, -18120));
     obstacles.push_back(make_pair(-26100, -15700));
     obstacles.push_back(make_pair(-26080, -18580));
     obstacles.push_back(make_pair(-26080, -18400));
     obstacles.push_back(make_pair(-26080, -18160));
     obstacles.push_back(make_pair(-26080, -18140));
     obstacles.push_back(make_pair(-26080, -15680));
     obstacles.push_back(make_pair(-26080, -11960));
     obstacles.push_back(make_pair(-26060, -18560));
     obstacles.push_back(make_pair(-26060, -18140));
     obstacles.push_back(make_pair(-26060, -15680));
     obstacles.push_back(make_pair(-26040, -18680));
     obstacles.push_back(make_pair(-26040, -18560));
     obstacles.push_back(make_pair(-26040, -18200));
     obstacles.push_back(make_pair(-26040, -18160));
     obstacles.push_back(make_pair(-26040, -18140));
     obstacles.push_back(make_pair(-26020, -18600));
     obstacles.push_back(make_pair(-26020, -18580));
     obstacles.push_back(make_pair(-26020, -18160));
     obstacles.push_back(make_pair(-26020, -15700));
     obstacles.push_back(make_pair(-26020, -15680));
     obstacles.push_back(make_pair(-26000, -18680));
     obstacles.push_back(make_pair(-26000, -18660));
     obstacles.push_back(make_pair(-26000, -18160));
     obstacles.push_back(make_pair(-26000, -11120));
     obstacles.push_back(make_pair(-25980, -18680));
     obstacles.push_back(make_pair(-25980, -18480));
     obstacles.push_back(make_pair(-25980, -18440));
     obstacles.push_back(make_pair(-25980, -18160));
     obstacles.push_back(make_pair(-25980, -18120));
     obstacles.push_back(make_pair(-25980, -18100));
     obstacles.push_back(make_pair(-25980, -15720));
     obstacles.push_back(make_pair(-25980, -15680));
     obstacles.push_back(make_pair(-25980, -13620));
     obstacles.push_back(make_pair(-25980, -10100));
     obstacles.push_back(make_pair(-25980, -10060));
     obstacles.push_back(make_pair(-25980, -10040));
     obstacles.push_back(make_pair(-25960, -18660));
     obstacles.push_back(make_pair(-25960, -18580));
     obstacles.push_back(make_pair(-25960, -18460));
     obstacles.push_back(make_pair(-25960, -18440));
     obstacles.push_back(make_pair(-25960, -18160));
     obstacles.push_back(make_pair(-25960, -18120));
     obstacles.push_back(make_pair(-25960, -13640));
     obstacles.push_back(make_pair(-25960, -10020));
     obstacles.push_back(make_pair(-25940, -18500));
     obstacles.push_back(make_pair(-25940, -18140));
     obstacles.push_back(make_pair(-25940, -15700));
     obstacles.push_back(make_pair(-25940, -15680));
     obstacles.push_back(make_pair(-25940, -13600));
     // will include more obstacles
        // Add more obstacles here
    //};

    // Calculate grid size
    int gridSizeX = abs(maxPosX - minPosX) / 100 + 1;
    int gridSizeY = abs(maxPosY - minPosY) / 100 + 1;

    cout << "Starting A* search..." << endl;

    double timeRemaining = performAStar((minPosX + abs(minPosX)) / 100, (minPosY + abs(minPosY)) / 100, 
                                        (maxPosX + abs(minPosX)) / 100, (maxPosY + abs(minPosY)) / 100, 
                                        averageSpeed, obstacles, gridSizeX, gridSizeY);

    if (timeRemaining >= 0) {
        cout << "Estimated time remaining: " << timeRemaining << " seconds" << endl;
    } else {
        cout << "Path not found!" << endl;
    }

    return 0;
}
