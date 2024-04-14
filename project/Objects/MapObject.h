#ifndef MAPOBJECT_H
#define MAPOBJECT_H

class TileGraph;
class Tile;

class MapObject
{
public:
    static TileGraph *_graph;
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
