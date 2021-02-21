#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int &selectedMap)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height))
{
  if (selectedMap == 2)
  {
    obstacle == nullptr;
  }
  else
  {
    this->obstacle = new Obstacle *[4];
    this->obstacle[0] = new Obstacle(DEFAULT_OBSTACLE_OFFSET, 0, DEFAULT_OBSTACLE_THICKNESS, DEFAULT_OBSTACLE_LENGTH);
    this->obstacle[1] = new Obstacle(static_cast<int>(grid_width) - DEFAULT_OBSTACLE_OFFSET, DEFAULT_OBSTACLE_OFFSET, DEFAULT_OBSTACLE_LENGTH, 1);
    this->obstacle[2] = new Obstacle(0, static_cast<int>(grid_height) - DEFAULT_OBSTACLE_OFFSET, DEFAULT_OBSTACLE_LENGTH, DEFAULT_OBSTACLE_THICKNESS);
    this->obstacle[3] = new Obstacle(static_cast<int>(grid_width) - DEFAULT_OBSTACLE_OFFSET, static_cast<int>(grid_height) - DEFAULT_OBSTACLE_OFFSET, DEFAULT_OBSTACLE_THICKNESS, DEFAULT_OBSTACLE_LENGTH);
  }

  loadHighestScore();
  PlaceFood(obstacle);
}

Game::~Game()
{
  if (obstacle != nullptr)
  {
    delete[] obstacle;
  }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool gamePaused = false;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, gamePaused);

    if (gamePaused)
    {
      renderer.Render(snake, food, gamePaused, obstacle);
      continue;
    }

    Update(this->obstacle);
    renderer.Render(snake, food, gamePaused, obstacle);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      // Update the time passed
      timePassed++;

      if (snake.alive) // Update the window title only if the snake is alive
      {
        renderer.UpdateWindowTitle(score, frame_count, timePassed);
      }

      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  if(score > highestScore)
  {
    saveHighestScore();
    std::cout << "Congratulations! You beat the highest score (" << highestScore << ")!" << std::endl;
    highestScore = score;
  }

}

void Game::PlaceFood(Obstacle **obs)
{
  bool place;
  int x, y;
  while (true)
  {
    place = true;
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a snake or by a obstacle item
    // before placing the food
    if (!snake.SnakeCell(x, y))
    {
      for (int i = 0; i < obs[0]->obsCount; i++)
      {
        if (obs[i]->obstacleCell(x, y))
        {
          place = false;
          break;
        }
      }
      if (place == true)
      {
        food.x = x;
        food.y = y;
        return;
      }
    }

  }
}

void Game::Update(Obstacle **obs)
{
  if (!snake.alive)
    return;

  snake.Update(obs);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood(obs);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetHighestScore() const { return highestScore; }

void Game::saveHighestScore()
{
  std::ofstream file("../save/highestScore.txt");
  file << score;
  file.close();
}

void Game::loadHighestScore()
{
  std::ifstream file("../save/highestScore.txt");
  
  if (file.is_open())
  {
    file >> highestScore;
    // check if the read score is valid
    if (!(highestScore < 1000 && highestScore > 0))
    {
      highestScore = 0;
    }    
  }
  else
  {
    highestScore = 0;
  }  
  file.close();
}