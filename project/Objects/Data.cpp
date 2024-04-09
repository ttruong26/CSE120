#include "Data.h"

Data::Data()
{
    _currentTile = new Tile(0, 0);
}

Data::Data(int x, int y)
{
    _currentTile = new Tile(x, y);
}

void Data::setPosition(int x, int y)
{
    _currentTile->setPosition(x, y);
}
