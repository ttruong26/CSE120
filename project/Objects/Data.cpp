#include "Data.h"

Data::Data()
{
    _currentTile = new Tile(0, 0);
}

Data::Data(int x, int y)
{
    _currentTile = new Tile(x, y);
    std::shared_ptr<Data> shared(this);
    _currentTile->setObject(shared);
}

void Data::setPosition(int x, int y)
{
    _currentTile->setPosition(x, y);
    std::shared_ptr<Data> shared(this);
    _currentTile->setObject(shared);
}
