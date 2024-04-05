#ifndef LINE_H
#define LINE_H

#include "MapObject.h"
#include "../TileGraph/Tile.h"
#include <vector>

class Line : public MapObject
{
public:
    Line();
    Line(int x1, int y1, int x2, int y2);

    void setEndPoints(Tile *start, Tile *end);
    void setEndPoints(int x1, int y1, int x2, int y2);

    Type getType() const override { return Type::Wall; }
    std::vector<Tile *> getTiles() { return _tiles; }
    void drawLine(); // Use Bresenhams algorithm to draw a line segment to connect the two endpoints, giving every point on the line an integer value for effeciency.

    void print() override
    {
        std::cout << "Start: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")";
        std::cout << ", End: (" << _endPoint->getPosition()._x << ", " << _endPoint->getPosition()._y << ")" << std::endl;
    }

    // Test
    void printLineSegment()
    {
        for (int i = 0; i < _tiles.size(); i++)
        {
            std::cout << "Tile " << i << ": (" << _tiles[i]->getPosition()._x << ", " << _tiles[i]->getPosition()._y << ")" << std::endl;
        }
    }

private:
    // We will use MapObject::currentTile to represent the starting point of the line.
    Tile *_endPoint;

    int _x1, _y1, _x2, _y2;
    std::vector<Tile *> _tiles; // Vector to represent the tiles that the line passes through.
};

#endif