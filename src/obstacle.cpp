#include "obstacle.h"

int Obstacle::obsCount = 0;

Obstacle::Obstacle(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height)
{
    obsCount++;
}

bool Obstacle::obstacleCell(int _x, int _y)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if ((x + i == _x) && (y + j == _y))
            {
                return true;
            }
        }
    }
    return false;
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