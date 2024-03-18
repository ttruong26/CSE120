#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "../Utility.h"

// Forward Declaration
class Robot;
class Goal;
class Wall;

class Tile
{
public:
    // Tile constructors for placing a tile on x-y grid
    Tile();
    Tile(int x, int y);

    void setPosition(int x, int y);
    Point getPosition();
    int getX();
    int getY();

    // AStar Properties
    int g = 0;
    int h = 0;
    int f = 0;
    Tile *parent = nullptr;
    void calculateHeuristic(const Point &target);
    void resetPathFindingInfo();

    void Print()
    {
        std::cout << "(" << coordinates._x << ", " << coordinates._y << ") ";
    }

    // Setters for different types of object that can be on tile
    void setRobot(Robot *robot);
    void setGoal(Goal *goal);
    void setWall(Wall *wall);

    // Getters for different types of object that can be on tile
    Robot *getRobot();
    Goal *getGoal();
    Wall *getWall();

private:
    Point coordinates;

    // Tile can either hold a robot, goal or wall element
    Robot *mRobot;
    Goal *mGoal;
};

#endif
