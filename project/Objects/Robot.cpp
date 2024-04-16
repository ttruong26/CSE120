#include "Robot.h"

Robot::Robot()
{
    robotId = 0;
    _currentTile = nullptr;
}

Robot::Robot(int x, int y, int id, double speed)
{
    robotId = id;
    avgSpeed = speed;
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

double Robot::predictTimeEstimation(Goal *goal)
{
    Tile *start = this->_currentTile;
    Tile *end = goal->getCurrentPosition();

    /*
    std::priority_queue<Tile *, std::vector<Tile *>, CompareTile> openSet; // This requires a comparator to sort by f cost
    std::unordered_set<Tile *> closedSet;
    std::unordered_set<Tile *> openSetItems;
    */

    start->g = 0;
    start->h = start->calculateHeuristic(end);
    start->f = start->g + start->h;
    start->parent = nullptr;

    /*
    openSet.push(start);
    openSetItems.insert(start);
    */

    // Initialize priority queue and visited array
    std::priority_queue<Tile *, std::vector<Tile *>, CompareTile> openSet;
    std::vector<std::vector<bool>> visited(_graph->getWidth(), std::vector<bool>(_graph->getHeight(), false));
    _graph->print();

    // Push the starting node onto the open set
    openSet.push(start);

    // A* search loop
    while (!openSet.empty())
    {
        // std::cout << "In" << std::endl;
        Tile *current = openSet.top();
        openSet.pop();

        // Check if goal reached
        if (current->getX() == end->getX() && current->getY() == end->getY())
        {
            std::cout << "Path Distance: " << current->g << "\n";
            return current->g / avgSpeed; // Return time to reach goal
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

bool Robot::avoidPath(Tile *tile)
{
    if (tile->isWall() == true)
        return true;
    return false;
}