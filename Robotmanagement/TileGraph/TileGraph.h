#ifndef TILEGRAPH_H
#define TILEGRAPH_H

#include "Tile.h"
#include <array>
#include <vector>

// EX: a Tile Graph with width 10 and height 10 starting at origin (-10, -10) would look like this:
//    Due to indexing the TileGraph will be 11x11
//    (-10 ,  0), (-9 , 0 ), (-8 ,  0), (-7 ,  0), (-6 ,  0), (-5 ,  0), (-4 ,  0), (-3 ,  0), (-2 ,  0), (-1 ,  0), (0 ,  0)
//    (-10 , -1), (-9 , -1), (-8 , -1), (-7 , -1), (-6 , -1), (-5 , -1), (-4 , -1), (-3 , -1), (-2 , -1), (-1 , -1), (0 , -1)
//    (-10 , -2), (-9 , -2), (-8 , -2), (-7 , -2), (-6 , -2), (-5 , -2), (-4 , -2), (-3 , -2), (-2 , -2), (-1 , -2), (0 , -2)
//    (-10 , -3), (-9 , -3), (-8 , -3), (-7 , -3), (-6 , -3), (-5 , -3), (-4 , -3), (-3 , -3), (-2 , -3), (-1 , -3), (0 , -3)
//    (-10 , -4), (-9 , -4), (-8 , -4), (-7 , -4), (-6 , -4), (-5 , -4), (-4 , -4), (-3 , -4), (-2 , -4), (-1 , -4), (0 , -4)
//    (-10 , -5), (-9 , -5), (-8 , -5), (-7 , -5), (-6 , -5), (-5 , -5), (-4 , -5), (-3 , -5), (-2 , -5), (-1 , -5), (0 , -5)
//    (-10 , -6), (-9 , -6), (-8 , -6), (-7 , -6), (-6 , -6), (-5 , -6), (-4 , -6), (-3 , -6), (-2 , -6), (-1 , -6), (0 , -6)
//    (-10 , -7), (-9 , -7), (-8 , -7), (-7 , -7), (-6 , -7), (-5 , -7), (-4 , -7), (-3 , -7), (-2 , -7), (-1 , -7), (0 , -7)
//    (-10 , -8), (-9 , -8), (-8 , -8), (-7 , -8), (-6 , -8), (-5 , -8), (-4 , -8), (-3 , -8), (-2 , -8), (-1 , -8), (0 , -8)
//    (-10 , -9), (-9 , -9), (-8 , -9), (-7 , -9), (-6 , -9), (-5 , -9), (-4 , -9), (-3 , -9), (-2 , -9), (-1 , -9), (0 , -9)
//    (-10 ,-10), (-9 ,-10), (-8 ,-10), (-7 ,-10), (-6 ,-10), (-5 ,-10), (-4 ,-10), (-3 ,-10), (-2 ,-10), (-1 ,-10), (0 ,-10)

class TileGraph
{
public:
    TileGraph();
    TileGraph(int w, int h, int originX, int originY);

    void setBounds(int w, int h, int originX, int originY);
    // Used for heuristic calculation in pathfinding.
    std::array<Tile *, 4> getNeighbors(Tile *tile);     // Returns the neighbors of given tile N,S,E,W
    std::array<Tile *, 8> getNeighborsDiag(Tile *tile); // Returns all surronding neighbors of given tile N,NE,NW...

    Tile *getTileAt(int x, int y);

    void placeGoal();
    Goal *getGoal(); // Return where Goal object is found on tile graph, potential use for robot pathfinding.

    int getWidth();
    int getHeight();

    void printGraph();
    void print();

private:
    int _width, _height;
    Point _origin;

    std::vector<std::vector<Tile>> tiles;
};

#endif // TILEGRAPH_H