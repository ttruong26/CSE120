#include "Robot.h"

Robot::Robot()
{
    robotId = 0;
    _currentTile = nullptr;
}

Robot::Robot(int x, int y, int id, double speed)
{
    robotId = id;
    _avgSpeed = speed;
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

void Robot::executeTask(Goal *goal)
{
}

Goal *Robot::getCurrentGoal()
{
    return currentGoal;
}

double Robot::predictTimeEstimation(std::shared_ptr<Goal> &goal)
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
    _mGraph->print();

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
            std::cout << "Path Distance: " << current->g << "\n";
            return current->g / _avgSpeed; // Return time to reach goal
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

    /*
    while (!openSet.empty())
    {
        std::cout << "Robot is finding path\n";
        Tile *current = openSet.top();
        openSet.pop();
        openSetItems.erase(current);

        // your existing logic
        if (current->getX() == end->getX() && current->getY() == end->getY())
        {
            return reconstructPath(current); // Function to calculate the path length
        }

        closedSet.insert(current);

        auto neighbors = _graph->getNeighbors(current); // Get neighbors of the current tile
        for (Tile *neighbor : neighbors)
        {
            if (!neighbor || closedSet.find(neighbor) != closedSet.end() || neighbor->isWall()) // Make sure the neighbor is not out of bounds, not already visited, and not a wall
                continue;

            double tentative_gScore = current->g + current->cost(neighbor);
            if (tentative_gScore < neighbor->g)
            {
                neighbor->parent = current;
                neighbor->g = tentative_gScore;
                neighbor->h = neighbor->calculateHeuristic(end);
                neighbor->f = neighbor->g + neighbor->h;
                if (openSetItems.find(neighbor) == openSetItems.end())
                {
                    openSet.push(neighbor);
                    openSetItems.insert(neighbor);
                }
            }
        }
    }
    */

    return -1; // If no path is found
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
