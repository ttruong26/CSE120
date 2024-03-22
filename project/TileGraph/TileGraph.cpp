#include "TileGraph.h"
#include <algorithm>

#include "TileGraph.h"
#include <algorithm>
#include <vector>

TileGraph::TileGraph()
{
    _width = 0;
    _height = 0;
    _origin = Point(0, 0);
    tiles = std::vector<std::vector<Tile *>>();
}

TileGraph::TileGraph(int w, int h, int originX, int originY)
{
    this->setBounds(w, h, originX, originY);
}

void TileGraph::setBounds(int w, int h, int originX, int originY)
{
    // We index from 0 to height + 1, and weight +1. This is because the # of points on a line of length n is n+1
    // Ex: 0,0 to 0,1 is 2 points but is a line segment of length 1.
    for (int y = 0; y < h + 1; y++)
    {
        tiles.push_back(std::vector<Tile *>());
        for (int x = 0; x < w + 1; x++)
        {
            Tile *tile = new Tile(originX + x, originY + y);
            tiles[y].push_back(tile);
        }
    }

    _origin = Point(originX, originY);
    _width = w;
    _height = h;
}

Tile *TileGraph::getTileAt(int x, int y)
{
    if (x < _origin._x || x >= _width + _origin._x || y < _origin._y || y >= _height + _origin._y)
    {
        std::cout << "Tile out of bounds" << std::endl;
        return NULL;
    }

    int indexX = x - _origin._x;
    int indexY = y - _origin._y;
    return tiles[indexY][indexX];
}

void TileGraph::placeTiletoArray(int x, int y, Tile *tile)
{
    int indexX = x - _origin._x;
    int indexY = y - _origin._y;
    tiles[indexY][indexX] = tile;
}

void TileGraph::placeObject(MapObject *object)
{
    // std::cout << object->getCurrentPosition()->getX() << object->getCurrentPosition()->getY() << std::endl;
    placeTiletoArray(object->getCurrentPosition()->getX(), object->getCurrentPosition()->getY(), object->getCurrentPosition());
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