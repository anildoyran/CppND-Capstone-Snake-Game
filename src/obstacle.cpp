#include "obstacle.h"

int Obstacle::obsCount = 0;

Obstacle::Obstacle(int _x, int _y, int _width, int _height)
{
    this->x = _x;
    this->y = _y;
    this->width = _width;
    this->height = _height;
    obsCount++;
}

int Obstacle::getxPos()
{
    return this->x;
}

int Obstacle::getyPos()
{
    return this->y;
}

int Obstacle::getWidth()
{
    return this->width;
}

int Obstacle::getHeight()
{
    return this->height;
}