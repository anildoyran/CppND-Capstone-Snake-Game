#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize surface for loading image
  surface = nullptr;
  pauseImage = nullptr;
}

Renderer::~Renderer()
{
  // Free the surfaces
  SDL_FreeSurface(pauseImage);
  SDL_FreeSurface(surface);

  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, bool &pause, Obstacle **obs)
{

  // Pause screen
  if (pause)
  {
    SDL_Rect rect;
    surface = SDL_GetWindowSurface(sdl_window);
    pauseImage = SDL_LoadBMP("../image/pause.bmp");

    // Locate the pause image at the center
    rect.x = (screen_width - pauseImage->w) / 2;
    rect.y = (screen_height - pauseImage->h) / 2;

    if (nullptr == pauseImage)
    {
      std::cout << "SDL could not load the image! SDL Error: " << SDL_GetError() << std::endl;
    }
    else
    {
      SDL_BlitSurface(pauseImage, NULL, surface, &rect);
      SDL_UpdateWindowSurface(sdl_window);
    }

    return;
  }

  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive)
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  }
  else
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render obstacles
  if (obs != nullptr)
  {
    for (int i = 0; i < obs[0]->obsCount; i++)
    {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
      block.x = obs[i]->getxPos() * (screen_width / grid_width);
      block.y = obs[i]->getyPos() * (screen_height / grid_height);
      block.w = obs[i]->getWidth() * (screen_width / grid_width);
      block.h = obs[i]->getHeight() * (screen_height / grid_height);
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, int time)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Time: " + std::to_string(time)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
