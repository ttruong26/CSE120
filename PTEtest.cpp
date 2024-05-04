#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>

using namespace std;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;

const int SPEED_MM_PER_SEC = 1200;

struct Node {
    int x, y;
    int g, h, f;
    Node* parent;

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {}

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

// Function to calculate Euclidean distance between two nodes
double euclideanDistance(const Node& node1, const Node& node2) {
    return sqrt(pow(node1.x - node2.x, 2) + pow(node1.y - node2.y, 2));
}

// Custom comparator for priority queue
struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->f > rhs->f;
    }
};

// A* algorithm implementation
vector<pair<int, int>> astar(const Node& start, const Node& goal, const vector<pair<int, int>>& avoidCoordinates) {
    priority_queue<Node*, vector<Node*>, CompareNode> openList;
    vector<Node*> closedList;
    unordered_set<pair<int, int>> avoidSet;

    for (const auto& coord : avoidCoordinates) {
        avoidSet.insert(coord);
    }

    openList.push(new Node(start));

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        closedList.push_back(current);

        if (*current == goal) {
            vector<pair<int, int>> path;
            while (current != nullptr) {
                path.emplace_back(current->x, current->y);
                current = current->parent;
            }
            return path;
        }

        // Generate children
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0)
                    continue;

                int newX = current->x + dx;
                int newY = current->y + dy;

                if (newX < 0 || newX >= GRID_WIDTH || newY < 0 || newY >= GRID_HEIGHT)
                    continue;

                if (avoidSet.count({newX, newY})) // Avoid this coordinate
                    continue;

                Node* newNode = new Node(newX, newY);
                newNode->parent = current;

                // Calculate costs
                newNode->g = current->g + euclideanDistance(*current, *newNode);
                newNode->h = euclideanDistance(*newNode, goal);
                newNode->f = newNode->g + newNode->h;

                // Check if the node is already in the closed list
                bool inClosedList = false;
                for (const auto& node : closedList) {
                    if (*node == *newNode) {
                        inClosedList = true;
                        break;
                    }
                }

                if (inClosedList)
                    continue;

                // Check if the node is already in the open list
                bool inOpenList = false;
                for (const auto& node : openList) {
                    if (*node == *newNode) {
                        inOpenList = true;
                        break;
                    }
                }

                if (!inOpenList)
                    openList.push(newNode);
            }
        }
    }

    return {}; // No path found
}

int main() {
    Node start(0, 0);
    Node goal(9, 9);

    vector<pair<int, int>> avoidCoordinates = {{3, 4}, {3, 5}, {4, 4}, {4, 5}};

    vector<pair<int, int>> path = astar(start, goal, avoidCoordinates);

    if (path.empty()) {
        cout << "No path found." << endl;
        return 0;
    }

    cout << "Path: ";
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        cout << "(" << it->first << ", " << it->second << ") ";
    }
    cout << endl;

    double totalDistance = 0;
    for (size_t i = 1; i < path.size(); ++i) {
        totalDistance += euclideanDistance(Node(path[i - 1].first, path[i - 1].second), Node(path[i].first, path[i].second));
    }

    double totalTime = totalDistance / SPEED_MM_PER_SEC;
    cout << "Total Time (seconds): " << totalTime << endl;

    return 0;
}
