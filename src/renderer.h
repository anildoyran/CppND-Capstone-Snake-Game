#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "obstacle.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, bool &pause, Obstacle **obs);
  void UpdateWindowTitle(int score, int fps, int time);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  SDL_Surface *surface;
  SDL_Surface *pauseImage;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif