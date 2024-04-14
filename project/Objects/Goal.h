#ifndef GOAL_H
#define GOAL_H

#include <iostream>
#include <string>
#include <ctime>
#include "MapObject.h"
#include "../graph/Tile.h"

class Goal : public MapObject
{
public:
    Goal();
    Goal(int x, int y, double heading, std::string id);

    Type getType() const override { return Type::Goal; } // Determine whether the MapObject is a Goal.
    void setPosition(int x, int y);

    bool isWorking() { return _isActive; } // Ensure robot multiple robots don't work on the same goal.

    void print() override
    {
        std::cout << "Goal ID: " << _goalId << ", Position: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << "), "
                  << "Heading: " << _heading << std::endl;
    }

private:
    std::string _goalId;
    double _heading;

    bool _isActive;
    double _size; // For consideration of a Goal taking up multiple tiles.

    // Time_t completionTime = time(0); //Time element for completion time.
};

#endif // GOAL_H