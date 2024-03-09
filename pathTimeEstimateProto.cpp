#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate distance between two points
double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
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

// Function to calculate time remaining
double calculateTimeRemaining(int minPosX, int minPosY, int maxPosX, int maxPosY, double averageSpeed, const vector<pair<int, int>>& obstacles) {
    double distance = 0;
    int currentX = minPosX;
    int currentY = minPosY;

    while (currentX != maxPosX || currentY != maxPosY) {
        int nextX = currentX;
        int nextY = currentY;

        if (currentX < maxPosX) {
            nextX++;
        } else if (currentX > maxPosX) {
            nextX--;
        }

        if (currentY < maxPosY) {
            nextY++;
        } else if (currentY > maxPosY) {
            nextY--;
        }

        if (!isInObstacle(nextX, nextY, obstacles)) {
            distance += calculateDistance(currentX, currentY, nextX, nextY);
            currentX = nextX;
            currentY = nextY;
        }
    }

    double time = distance / averageSpeed; // Time = Distance / Speed
    return time;
}

int main() {
    int minPosX = -26100;
    int minPosY = -19900;
    int maxPosX = -15840;
    int maxPosY = -4860;
    double averageSpeed = 1200; // in mm/sec

    // Define obstacle areas
    vector<pair<int, int>> obstacles = {
        {-26100, -18640},
        {-26100, -18540},
        {-26100, -18520},
        {-26100, -18440},
        {-26100, -18400},
        {-26100, -18360},
        {-26100, -18340},
        {-26100, -18320},
        {-26100, -18300},
        {-26100, -18280},
        {-26100, -18140},
        {-26100, -18120},
        {-26100, -15700},
        {-26080, -18580},
        {-26080, -18400},
        {-26080, -18160},
        {-26080, -18140},
        {-26080, -15680},
        {-26080, -11960},
        {-26060, -18560},
        {-26060, -18140},
        {-26060, -15680},
        {-26040, -18680},
        {-26040, -18560},
        {-26040, -18200},
        {-26040, -18160},
        {-26040, -18140},
        {-26020, -18600},
        {-26020, -18580},
        {-26020, -18160},
        {-26020, -15700},
        {-26020, -15680},
        {-26000, -18680},
        {-26000, -18660},
        {-26000, -18160},
        {-26000, -11120},
        {-25980, -18680},
        {-25980, -18480},
        {-25980, -18440},
        {-25980, -18160},
        {-25980, -18120},
        {-25980, -18100},
        {-25980, -15720},
        {-25980, -15680},
        {-25980, -13620},
        {-25980, -10100},
        {-25980, -10060},
        {-25980, -10040},
        {-25960, -18660},
        {-25960, -18580},
        {-25960, -18460},
        {-25960, -18440},
        {-25960, -18160},
        {-25960, -18120},
        {-25960, -13640},
        {-25960, -10020},
        {-25940, -18500},
        {-25940, -18140},
        {-25940, -15700},
        {-25940, -15680},
        {-25940, -13600}
    };

    double timeRemaining = calculateTimeRemaining(minPosX, minPosY, maxPosX, maxPosY, averageSpeed, obstacles);

    cout << "Time remaining: " << timeRemaining << " seconds" << endl;

    return 0;
}
