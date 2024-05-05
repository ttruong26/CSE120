#include "Robot.h"
#include <math.h>

Robot::Robot()
{
    _robotId = 0;
    _currentTile = nullptr;
    _isFree = true;
}

Robot::Robot(int x, int y, int id, double speed)
{
    _robotId = id;
    _avgSpeed = speed;
    _isFree = true;
    this->setPosition(x, y);
}

void Robot::setPosition(Tile *tile)
{
    _currentTile = tile;
}

void Robot::setPosition(int x, int y)
{
    _currentTile = new Tile(x, y);

    std::shared_ptr<Robot> shared(this);
    _currentTile->setObject(shared);
}

void Robot::moveTo(int x, int y)
{
    if (_mGraph->getTileAt(x, y)) // Check if their is an object at the next tile.
    {
        this->setPosition(x, y);
        _mGraph->placeObject(this);
    }
}

void Robot::assignTask(std::shared_ptr<Goal> goal)
{
    currentGoal = goal.get();
    _isFree = false;
    _currentRun._goalPosition = goal->getCurrentPosition()->getPosition();
    _currentRun._robotStartPos = _currentTile->getPosition();
}

void Robot::finishTask(double timeTaken)
{
    _isFree = true;
    _currentRun._timeTaken = timeTaken;
    _previousRuns[currentGoal->getGoalId()].push_back(_currentRun);
}

Goal *Robot::getCurrentGoal()
{
    return currentGoal;
}

double Robot::predictTimeEstimation(std::shared_ptr<Goal> goal)
{
    Tile *start = this->_currentTile;
    Tile *end = goal->getCurrentPosition();

    start->g = 0;
    start->h = start->calculateHeuristic(end);
    start->f = start->g + start->h;
    start->parent = nullptr;

    // Initialize priority queue and visited array
    std::priority_queue<Tile *, std::vector<Tile *>, CompareTile> openSet;
    std::vector<std::vector<bool>> visited(_mGraph->getWidth(), std::vector<bool>(_mGraph->getHeight(), false));
    std::cout << "Computing path distance from ";
    start->Print();
    std::cout << "to ";
    end->Print();
    std::cout << std::endl;

    // Push the starting node onto the open set
    openSet.push(start);

    // A* search loop
    while (!openSet.empty())
    {
        // std::cout << "In" << std::endl; // gets to here
        Tile *current = openSet.top();
        openSet.pop();

        // Check if goal reached
        if (current->getX() == end->getX() && current->getY() == end->getY())
        {
            int initialEstimate = current->g / _avgSpeed;
            std::cout << "Path Distance:";
            std::cout << ": " << current->g << "\n";
            std::cout << "Initial Estimate to reach goal:";
            std::cout << ": " << initialEstimate << "sec\n";

            double adjustedEstimate = weightedAverageTime(goal);
            if (adjustedEstimate != -1)
            {
                return adjustedEstimate; // Or some combination of initialEstimate and adjustedEstimate
            }
            return initialEstimate; // Return time to reach goal
        }

        // Check if node is already visited or in an obstacle
        if (visited[_mGraph->getXIndex(current)][_mGraph->getYIndex(current)] || current->isWall())
        {
            continue; // Skip this node
        }

        // Mark node as visited
        visited[_mGraph->getXIndex(current)][_mGraph->getYIndex(current)] = true;

        // Iterate over neighbor nodes
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int nextX = current->getX() + dx;
                int nextY = current->getY() + dy;
                Tile *next = _mGraph->getTileAt(nextX, nextY);

                // Check if neighbor node is within grid bounds
                if (!next || _mGraph->getXIndex(next) < 0 || _mGraph->getXIndex(next) >= _mGraph->getWidth() || _mGraph->getYIndex(next) < 0 || _mGraph->getYIndex(next) >= _mGraph->getHeight())
                {
                    continue;
                }

                // Calculate new cost to reach neighbor node
                double newCost = current->g + current->calculateHeuristic(next);

                // Check if neighbor node is not visited and not in an obstacle
                if (!visited[_mGraph->getXIndex(next)][_mGraph->getYIndex(next)] && !next->isWall())
                {
                    // Calculate heuristic cost (distance to goal)
                    next->h = next->calculateHeuristic(end);
                    next->g = newCost;
                    next->f = newCost + next->h;

                    // Push neighbor node onto open set
                    openSet.push(next);
                }
            }
        }
    }

    return -1; // If no path is found
}

double Robot::weightedAverageTime(std::shared_ptr<Goal> goal)
{
    auto it = _previousRuns.find(goal->getGoalId());
    if (it != _previousRuns.end())
    {
        double weighted_sum = 0.0;
        double weight_total = 0.0;

        for (const auto &info : it->second)
        {
            // Find the euclidean distance between the robot's current position and the position of the robot that collected the data
            double distance = sqrt(pow(_currentTile->getX() - info._robotStartPos._x, 2) + pow(_currentTile->getY() - info._robotStartPos._y, 2));
            double weight = 1.0 / (distance + 1.0); // Adding 1 to avoid division by zero and reduce the impact of very small distances

            weighted_sum += info._timeTaken * weight;
            weight_total += weight;
        }
        return weighted_sum / weight_total;
    }
    return -1; // No historical data found
}

double Robot::reconstructPath(Tile *end)
{
    double pathLength = 0;
    Tile *current = end;
    while (current->parent)
    {
        pathLength++;
        current = current->parent;
    }
    return pathLength;
}
