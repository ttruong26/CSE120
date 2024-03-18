#include <iostream>
#include <string>
#include "TileGraph/TileGraph.h"
#include "Objects/Goal.h"
#include "Utility.h"
#include "static/ExtractContent.h"

#include "Objects/Workspace.h"

int main()
{
    Rect bounds = ExtractContent::extractBounds("mapfiles/test.map");
    std::cout << "Width: " << bounds._width << " Height: " << bounds._height << " BotLeftX: " << bounds._botLeftX << " BotLeftY: " << bounds._botLeftY << std::endl;

    TileGraph map(bounds._width, bounds._height, bounds._botLeftX, bounds._botLeftY);

    std::vector<Goal *> goals = ExtractContent::extractGoals("mapfiles/test.map");
    for (auto goal : goals)
    {
        goal->print();
    }

    TileGraph tg(10, 10, -10, -10);
    tg.printGraph();
    Tile *tile = tg.getTileAt(-3, -3);
    tile->Print();

    Workspace ws;
    ws.loadData();
    ws.print();

    return 0;
}