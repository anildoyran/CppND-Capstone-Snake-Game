#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
public:
    // Obstacle object constructor
    Obstacle(int _x, int _y, int _width, int _height);
    
    // NUmber of obstacle object created
    static int obsCount;

    // Check if the given cell is occupied by the obstacle
    bool obstacleCell(int _x, int _y);

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