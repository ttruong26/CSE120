#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <memory>

class TileGraph;
class Tile;

// Base class for all objects that can be placed on the TileMap
// MapObjects hold a pointer to the tile they are currently on, which lets us know their position.
// Can be one of three types: Robot, Goal, Wall. The default type is None.
class MapObject
{
public:
    static TileGraph *_mGraph; // Pointer to the graph that holds all the mapObjects. So we can access the graph from anywhere.
    enum class Type
    {
        Robot,
        Goal,
        Wall,
        None
    };

    virtual Type getType() const = 0;
    virtual void print() = 0;
    Tile *getCurrentPosition() { return _currentTile; }

protected:
    Tile *_currentTile;
};

#endif // MAPOBJECT_H
