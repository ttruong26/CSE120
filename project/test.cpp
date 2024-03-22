#include "TileGraph/TileGraph.h"
#include "Objects/Goal.h"
#include "Utility.h"

#include "Objects/Workspace.h"

int main()
{

    TileGraph tg(10, 10, -10, -10);
    tg.printGraph();
    Tile *tile = tg.getTileAt(-3, -3);
    tile->Print();

    Workspace ws;
    ws.loadData();
    ws.printGoals();
    ws.placeLoadedGoals();

    return 0;
}