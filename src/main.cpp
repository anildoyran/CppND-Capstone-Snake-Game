#include <iostream>
#include <thread>
#include "controller.h"
#include "game.h"
#include "renderer.h"

// Static function prototype
static void getUserInput(int &map);

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  int selectedMap;
  getUserInput(selectedMap);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, selectedMap);

  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Highest Score: " << game.GetHighestScore() << "\n";
  return 0;
}

static void getUserInput(int &map)
{
  std::cout << "Please select the map: Write 1 or 2\n"
            << std::endl;
  std::cout << "**********\t\t**********\n"
            << "*  *     *\t\t*        *\n"
            << "*  *     *\t\t*        *\n"
            << "*  *  ****\t\t*        *\n"
            << "*        *\t\t*        *\n"
            << "*        *\t\t*        *\n"
            << "****  *  *\t\t*        *\n"
            << "*     *  *\t\t*        *\n"
            << "*     *  *\t\t*        *\n"
            << "**********\t\t**********\n";
  std::cout << "1- w/Obstacle\t\t2- Blank\n";
  std::cout << "Your choice: ";
  std::cin >> map;

  if (!(map == 1 || map == 2))
  {
    std::cout << "Invalid map selection!\nThe default blank map is opening..." << std::endl;
    map = 2;
  }

  for (int i = 3; i > 0; i--)
  {
    std::cout << "** " << i << " **" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  std::cout << "The game has started!" << std::endl;
}