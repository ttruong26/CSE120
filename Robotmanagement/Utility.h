#pragma once

struct Point
{
    int _x;
    int _y;

    Point()
    {
        _x = 0;
        _y = 0;
    }

    Point(int x, int y)
    {
        this->_x = x;
        this->_y = y;
    }
};

struct Rect
{
    int _width;
    int _height;
    int _botLeftX;
    int _botLeftY;

    Rect()
    {
        _width = 0;
        _height = 0;
        _botLeftX = 0;
        _botLeftY = 0;
    }

    Rect(int w, int h, int x, int y)
    {
        _width = w;
        _height = h;
        _botLeftX = x;
        _botLeftY = y;
    }
};