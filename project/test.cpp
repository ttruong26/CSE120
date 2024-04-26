#include <iostream>
#include <string>
#include "Objects/Goal.h"
#include "include/Utility.h"

#include "Objects/Workspace.h"

int main()
{
    TileGraph *tg = new TileGraph(100, 100, -100, -100); // Create a 100x100 graph with the origin at (-100, -100)
    MapObject::_mGraph = tg;                             // Set the graph for the MapObject class

    std::shared_ptr<Goal> goal1 = std::make_shared<Goal>(-15, -10, 0.0, "goal1"); // Create a goal at (-15, -10) with heading 0

    // Another way of creating a goal and setting its position
    std::shared_ptr<Goal> goal2 = std::make_shared<Goal>();
    goal2->setPosition(-10, -15);
    tg->placeObject(goal1.get()); // We need to place the goal on the graph to be able

    // Create the robot using a constructor that takes x, y, heading, and speed
    Robot *robot = new Robot(-99, -99, 0, 1);
    tg->placeObject(robot);

    double distance = robot->predictTimeEstimation(goal1);
    std::cout << "Distance: " << distance << std::endl;

    Workspace ws;
    ws.loadData();
    ws.printGoals();

    ws.cleanUp();

    return 0;
}