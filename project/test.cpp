#include <iostream>
#include <string>
#include "Objects/Goal.h"
#include "include/Utility.h"

#include "Objects/Workspace.h"

int main()
{
    /*
    /// Test the TileGraph class while placing goals and robots. Tests the a* algorithm from Robots to Goals
    ///
    TileGraph *tg = new TileGraph(2000, 2000, -2000, -2000); // Create a 2000x2000 graph with the origin at (-2000, -2000)
    MapObject::_mGraph = tg;                                 // Set the graph for the MapObject class

    // Create a goal at (-1, -1) with heading 0.0 and id "goal1"
    std::shared_ptr<Goal> goal1 = std::make_shared<Goal>(-1, -1, 0.0, "goal1");

    // Another way of creating a goal and setting its position
    std::shared_ptr<Goal> goal2 = std::make_shared<Goal>();
    goal2->setPosition(-1000, -0);
    tg->placeObject(goal1.get()); // We need to place the goal on the graph to be able
    tg->placeObject(goal2.get());

    // Create the robot using a constructor that takes x, y, heading, and speed
    int robotPosX = -2000, robotPosY = -2000;
    Robot *robot = new Robot(robotPosX, robotPosY, 0, 1);
    tg->placeObject(robot);

    double testDistance = robot->predictTimeEstimation(goal1);
    std::cout << "Time Prediction: " << testDistance << std::endl;
    double testDistance2 = robot->predictTimeEstimation(goal2);
    std::cout << "Time Prediction: " << testDistance2 << std::endl
              << std::endl;
    ///
    /// End of TileGraph test
    */

    // Creates the workspace object
    Workspace ws;
    ws.loadData(); // Grab relevant information from mapfile and creates workspace with Goals and Obstacles as coordinate Graph.
                   // Also creates Robots and assigns them to Goals.

    std::vector<Robot *> robots = ws.createRobots(5);

    ws.printGoals(); // List loaded goals
    std::cout << std::endl;

    std::cout << "Assignment Table" << std::endl;
    ws.printAssignmentTable();
    std::cout << std::endl;

    Robot *robot1 = ws.getAssignedRobot("Goal113");
    std::cout << std::endl;
    robot1->print();
    std::cout << std::endl;
    robot1->moveTo(-2000, -500);
    robot1->print();
    std::cout << std::endl;

    ws.updateAssignmentTable();
    ws.printAssignmentTable();

    // ws.assignAllRobots();

    ws.setRobotWorking(robot1);

    // ws.cleanUp();

    return 0;
}