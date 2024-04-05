#include "Line.h"
#include <cmath>
#include <algorithm>

Line::Line()
{
    _x1 = 0;
    _y1 = 0;
    _x2 = 0;
    _y2 = 0;
}

// Constructor
// (x1, y1): Starting point of the line
// (x2, y2): Ending point of the line
Line::Line(int x1, int y1, int x2, int y2)
{
    this->setEndPoints(x1, y1, x2, y2);
}

void Line::setEndPoints(Tile *start, Tile *end)
{
    _currentTile = start;
    _endPoint = end;
}

// (x1, y1): Starting point of the line
// (x2, y2): Ending point of the line
void Line::setEndPoints(int x1, int y1, int x2, int y2)
{
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;

    // Create tileObjects from the input coordinates, and set the tile object to a Wall/Line
    _currentTile = new Tile(x1, y1);
    _endPoint = new Tile(x2, y2);
    _currentTile->setObject(this);
    _endPoint->setObject(this);

    // Given the two endpoints, draw a line segment to connect the two points
    this->drawLine();
}

// Line has a start and end point. se Bresenham's line algorithm to place a tile on the linesegment
// and place the appropriate tiles for the line
void Line::drawLine()
{
    // Draw the line on the map
    bool steep = std::abs(_y2 - _y1) > std::abs(_x1 - _x2);
    if (steep)
    {
        std::swap(_x1, _y1);
        std::swap(_x2, _y2);
    }

    if (_x1 > _x2)
    {
        std::swap(_x1, _x2);
        std::swap(_y1, _y2);
    }

    int deltaX = _x2 - _x1;
    int deltaY = std::abs(_y2 - _y1);
    int error = deltaX / 2;
    int yStep = (_y1 < _y2) ? 1 : -1;
    int y = _y1;

    for (int x = _x1; x <= _x2; x++)
    {
        Tile *tempTile = new Tile();
        if (steep)
        {
            // Modify the tile at (y, x) to represent the line
            tempTile->setPosition(y, x);
            tempTile->setObject(this);
            _tiles.push_back(tempTile);
        }
        else
        {
            // Modify the tile at (x, y) to represent the line
            tempTile->setPosition(x, y);
            tempTile->setObject(this);
            _tiles.push_back(tempTile);
        }

        error -= deltaY;
        if (error < 0)
        {
            y += yStep;
            error += deltaX;
        }
    }
}