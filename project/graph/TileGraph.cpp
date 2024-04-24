#include "TileGraph.h"
#include <algorithm>

#include <algorithm>
#include <vector>

TileGraph::TileGraph()
{
    _width = 0;
    _height = 0;
    _origin = Point(0, 0);
    tiles = std::vector<std::vector<Tile *>>();
}

// Constructor that creates a rectangle on a cartesian plane starting at an origin (x,y). Represents a graph of tiles
// w: width of the graph
// h: height of the graph
// originX: x position of the origin
// originY: y position of the origin
TileGraph::TileGraph(int w, int h, int originX, int originY)
{
    this->setBounds(w, h, originX, originY);
}

// Helper function to set the bounds of the graph
void TileGraph::setBounds(int w, int h, int originX, int originY)
{
    // We index from 0 to height + 1, and weight +1. This is because the # of points on a line of length n is n+1
    // Ex: 0,0 to 0,1 is 2 points but is a line segment of length 1.
    for (int y = 0; y <= h; y++)
    {
        tiles.push_back(std::vector<Tile *>());
        for (int x = 0; x <= w; x++)
        {
            Tile *tile = new Tile(originX + x, originY + y);
            tiles[y].push_back(tile);
        }
    }

    this->_origin.setPoint(originX, originY);
    this->_width = w;
    this->_height = h;
}

Tile *TileGraph::getTileAt(int x, int y)
{

    try
    {
        if (x < _origin._x || x > _width + _origin._x || y < _origin._y || y > _height + _origin._y)
        {
            throw std::out_of_range("Cannot Access Tile out of bounds");
        }
        else
        {
            int indexX = x - _origin._x;
            int indexY = y - _origin._y;
            return tiles[indexY][indexX];
        }
    }
    catch (const std::out_of_range &e)
    {
        // std::cerr << e.what() << " (" << x << " " << y << ")" << std::endl;
        return NULL;
    }

    /*
     if (x < _origin._x || x > _width + _origin._x || y < _origin._y || y > _height + _origin._y)
     {

         std::cout << "Cannot Access Tile out of bounds"
                   << " (" << x << " " << y << ")" << std::endl;

         return NULL;
     }

     else
     {
         int indexX = x - _origin._x;
         int indexY = y - _origin._y;
         return tiles[indexY][indexX];
     }
     */
}

int TileGraph::getXIndex(Tile *tile)
{
    return tile->getPosition()._x - _origin._x;
}

int TileGraph::getYIndex(Tile *tile)
{
    return tile->getPosition()._y - _origin._y;
}

// Convert (x,y) to array indicies and place the tile in the array
void TileGraph::placeTiletoArray(int x, int y, Tile *tile)
{

    if (x < _origin._x || x >= _width + _origin._x || y < _origin._y || y >= _height + _origin._y)
    {
        std::cout << "Cannot Place Tile out of bounds"
                  << " (" << x << " " << y << ") " << std::endl;
    }

    else
    {
        int indexX = x - _origin._x;
        int indexY = y - _origin._y;
        tiles[indexY][indexX] = tile;
    }
}

void TileGraph::placeObject(MapObject *object)
{
    // Line behavior is different from other objects. Has a start and endpoint, with a line connecting the two points.
    // Integer points lying on the line are generated in the Line object, and all of the tiles need to be stored in the tile array
    Line *line = dynamic_cast<Line *>(object);
    if (line != nullptr)
    {
        // Get the xPosition, yPosition, and currTile from the Line, and place it in the tile array
        for (int i = 0; i < line->getTiles().size(); i++)
        {
            placeTiletoArray(line->getTiles()[i]->getX(), line->getTiles()[i]->getY(), line->getTiles()[i]);
        }
    }

    else
    {
        // Get the xPosition, yPosition, and currTile from a mapObject, and place it in the tile array
        placeTiletoArray(object->getCurrentPosition()->getX(), object->getCurrentPosition()->getY(), object->getCurrentPosition());
    }
}

int TileGraph::getWidth()
{
    return _width;
}

int TileGraph::getHeight()
{
    return _height;
}

void TileGraph::printGraph()
{
    for (int y = _height; y >= 0; y--)
    {
        for (int x = 0; x <= _width; x++)
        {
            tiles[y][x]->Print();
        }
        std::cout << std::endl;
    }
}

void TileGraph::print()
{
    std::cout << "Width: " << _width << " Height: " << _height << " OriginX: " << _origin._x << " OriginY: " << _origin._y << std::endl;
}

std::array<Tile *, 4> TileGraph::getNeighbors(Tile *tile)
{
    std::array<Tile *, 4> neighbours;

    int x = tile->getPosition()._x;
    int y = tile->getPosition()._y;

    neighbours[0] = getTileAt(x, y + 1); // N
    neighbours[1] = getTileAt(x + 1, y); // E
    neighbours[2] = getTileAt(x, y - 1); // S
    neighbours[3] = getTileAt(x - 1, y); // W

    return neighbours;
}

std::array<class Tile *, 8> TileGraph::getNeighborsDiag(class Tile *tile)
{
    std::array<Tile *, 8> neighbours;

    int x = tile->getPosition()._x;
    int y = tile->getPosition()._y;

    neighbours[0] = getTileAt(x, y + 1);     // N
    neighbours[1] = getTileAt(x + 1, y);     // E
    neighbours[2] = getTileAt(x, y - 1);     // S
    neighbours[3] = getTileAt(x - 1, y);     // W
    neighbours[4] = getTileAt(x + 1, y + 1); // NE
    neighbours[5] = getTileAt(x - 1, y + 1); // SE
    neighbours[6] = getTileAt(x - 1, y - 1); // SW
    neighbours[7] = getTileAt(x + 1, y - 1); // NW

    return neighbours;
}