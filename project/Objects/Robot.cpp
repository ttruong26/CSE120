#include "Robot.h"

Robot::Robot()
{
    robotId = 0;
    _currentTile = nullptr;
}

Robot::Robot(int x, int y, int id)
{
    robotId = id;
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

double Robot::findPathDistance(Goal *goal)
{
    Tile *start = this->_currentTile;
    Tile *end = goal->getCurrentPosition();

    std::priority_queue<Tile *, std::vector<Tile *>, CompareTile> openSet; // This requires a comparator to sort by f cost
    std::unordered_set<Tile *> closedSet;
    std::unordered_set<Tile *> openSetItems;

    start->g = 0;
    start->h = start->calculateHeuristic(end);
    start->f = start->g + start->h;
    start->parent = nullptr;

    openSet.push(start);

    while (!openSet.empty())
    {
        Tile *current = openSet.top();
        openSet.pop();
        openSetItems.erase(current);

        // your existing logic
        if (current == end)
        {
            return reconstructPath(current); // Function to calculate the path length
        }

        closedSet.insert(current);

        /*
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
        */
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

bool Robot::avoidPath(Tile *tile)
{
    if (tile->isWall() == true)
        return true;
    return false;
}