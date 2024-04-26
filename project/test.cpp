#include <iostream>
#include <string>
#include "Objects/Goal.h"
#include "include/Utility.h"

#include "Objects/Workspace.h"

int main()
{
    /*
    TileGraph tg(11, 11, -10, -10);
    tg.printGraph();
    Tile *tile = tg.getTileAt(0, 0);
    tile->Print();
    delete tile;
    */

    Workspace ws;
    ws.loadData();
    ws.printGoals();

    ws.cleanUp();

    return 0;
}