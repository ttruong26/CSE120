#include <iostream>
#include <cmath>
#include <cassert>

// Function for testing distance calculation
void testCalculateDistance() {
    double result = calculateDistance(0, 0, 3, 4);
    assert(fabs(result - 500.0) < 0.001); // Check if the distance calculation is correct, considering millimeter conversion
    cout << "testCalculateDistance passed." << endl;
}

// Function for testing obstacle detection
void testIsInObstacle() {
    vector<pair<int, int>> obstacles = {{1, 2}, {3, 4}};
    assert(isInObstacle(1, 2, obstacles) == true);  // Expect true
    assert(isInObstacle(2, 3, obstacles) == false); // Expect false
    cout << "testIsInObstacle passed." << endl;
}

// Function to test the overall A* search (a simplified scenario)
void testPerformAStar() {
    vector<pair<int, int>> obstacles = {{1, 1}, {2, 2}, {3, 3}};
    vector<pair<int, int>> lineSegments = {{1, 2, 1, 3}, {3, 3, 4, 4}};
    int gridSizeX = 5;
    int gridSizeY = 5;
    double result = performAStar(0, 0, 4, 4, 1000, obstacles, lineSegments, gridSizeX, gridSizeY);
    assert(result >= 0.0); // Expect a non-negative result indicating path found
    cout << "testPerformAStar passed." << endl;
}

void testNavigateSimpleObstacle() {
    vector<pair<int, int>> obstacles = {{1, 1}, {1, 2}, {1, 3}};
    vector<pair<int, int>> lineSegments;  // Assuming no line segments for simplicity
    int gridSizeX = 5, gridSizeY = 5;
    double expectedTime = performAStar(0, 0, 4, 4, 1000, obstacles, lineSegments, gridSizeX, gridSizeY);
    assert(expectedTime > 0); // Expect a positive time, indicating a path was found
    cout << "testNavigateSimpleObstacle passed." << endl;
}


