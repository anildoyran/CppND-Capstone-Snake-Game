#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include <fstream>
#include <iostream>

// Defined macros
#define DEFAULT_OBSTACLE_LENGTH 10
#define DEFAULT_OBSTACLE_THICKNESS 1
#define DEFAULT_OBSTACLE_OFFSET 10

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height, int &selectedMap);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetHighestScore() const;

private:
  Snake snake;
  SDL_Point food;
  Obstacle **obstacle;

  int highestScore;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int timePassed{0};

  void PlaceFood(Obstacle **obs);
  void Update(Obstacle **obs);
  
  // load and save the highest score
  void saveHighestScore();
  void loadHighestScore();
};

#endif