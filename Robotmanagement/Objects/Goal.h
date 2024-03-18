#ifndef GOAL_H
#define GOAL_H

#include <iostream>
#include <string>
#include "../Utility.h"
#include "../TileGraph/Tile.h"
#include <ctime>
#include "MapObject.h"

class Goal : public MapObject
{
public:
    Goal();
    Goal(Tile *tile, int id);
    Goal(int x, int y, double heading, std::string id);

    void setPosition(Tile *tile);
    void setPosition(int x, int y);
    Tile *getCurrentPosition();
    bool isWorking() { return _isActive; }

    void print()
    {
        std::cout << "Goal ID: " << _goalId << ", Position: (" << currentTile->getPosition()._x << ", " << currentTile->getPosition()._y << "), "
                  << "Heading: " << _heading << std::endl;
    }

private:
    std::string _goalId;
    double _heading;
    Tile *currentTile;

    bool _isActive;
    double _size; // For consideration of a Goal taking up multiple tiles.

    // Time_t completionTime = time(0); //Time element for completion time.
};

#endif // GOAL_H