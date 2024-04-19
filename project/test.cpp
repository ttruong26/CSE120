#include <iostream>
#include <string>
#include "Objects/Goal.h"
#include "Utility.h"

#include "Objects/Workspace.h"

int main()
{

    TileGraph tg(10, 10, -10, -10);
    tg.printGraph();
    Tile *tile = tg.getTileAt(0, 0);
    tile->Print();

    Workspace ws;
    ws.loadData();
    ws.printGoals();

    return 0;
}