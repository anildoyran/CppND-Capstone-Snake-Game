#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
public:
    Obstacle(int _x, int _y, int _width, int _height);
    static int obsCount;

    // getter functions
    int getxPos();
    int getyPos();
    int getWidth();
    int getHeight();

private:
    int x;
    int y;
    int width;
    int height;
};

#endif