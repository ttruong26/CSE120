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
    _currentTile->setObject(this);
}

void Robot::executeTask(Goal *goal)
{
}

Goal *Robot::getCurrentGoal()
{
    return currentGoal;
}

double Robot::predictTimeEstimation(std::unique_ptr<Goal> &goal)
{
    Tile *start = this->_currentTile;
    Tile *end = goal->getCurrentPosition();

    start->g = 0;
    start->h = start->calculateHeuristic(end);
    start->f = start->g + start->h;
    start->parent = nullptr;

    // Initialize priority queue and visited array
    std::priority_queue<Tile *, std::vector<Tile *>, CompareTile> openSet;
    std::vector<std::vector<bool>> visited(_graph->getWidth(), std::vector<bool>(_graph->getHeight(), false));
    _graph->print();

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
        if (visited[_graph->getXIndex(current)][_graph->getYIndex(current)] || current->isWall())
        {
            continue; // Skip this node
        }

        // Mark node as visited
        visited[_graph->getXIndex(current)][_graph->getYIndex(current)] = true;

        // Iterate over neighbor nodes
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                int nextX = current->getX() + dx;
                int nextY = current->getY() + dy;
                Tile *next = _graph->getTileAt(nextX, nextY);

                // Check if neighbor node is within grid bounds
                if (!next || _graph->getXIndex(next) < 0 || _graph->getXIndex(next) >= _graph->getWidth() || _graph->getYIndex(next) < 0 || _graph->getYIndex(next) >= _graph->getHeight())
                {
                    continue;
                }

                // Calculate new cost to reach neighbor node
                double newCost = current->g + current->calculateHeuristic(next);

                // Check if neighbor node is not visited and not in an obstacle
                if (!visited[_graph->getXIndex(next)][_graph->getYIndex(next)] && !next->isWall())
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
