#ifndef LINE_H
#define LINE_H

#include "MapObject.h"
#include "../graph/Tile.h"
#include <vector>

class Line : public MapObject
{
public:
    Line();
    Line(int x1, int y1, int x2, int y2);

    // Setter to place end points of line.
    void setEndPoints(Tile *start, Tile *end);
    void setEndPoints(int x1, int y1, int x2, int y2);

    Type getType() const override { return Type::Wall; }

    std::vector<Tile *> getTiles() { return _lineSegment; }

    void drawLine(); // Use Bresenhams algorithm to draw a line segment that connects the two endpoints, giving every point on the line an integer value for effeciency.

    void print() override
    {
        std::cout << "Start: (" << _currentTile->getPosition()._x << ", " << _currentTile->getPosition()._y << ")";
        std::cout << ", End: (" << _endPoint->getPosition()._x << ", " << _endPoint->getPosition()._y << ")" << std::endl;
    }

    // Test
    void printLineSegment()
    {
        for (int i = 0; i < _lineSegment.size(); i++)
        {
            std::cout << "Tile " << i << ": (" << _lineSegment[i]->getPosition()._x << ", " << _lineSegment[i]->getPosition()._y << ")" << std::endl;
        }
    }

private:
    // We will use MapObject::currentTile to represent the starting point of the line.
    Tile *_endPoint;

    int _x1, _y1, _x2, _y2;
    std::vector<Tile *> _lineSegment; // Vector to represent the tiles that the line passes through.
};

#endif