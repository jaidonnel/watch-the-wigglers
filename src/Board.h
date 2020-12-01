#pragma once
#include <vector>
#include "Ladder.h"
#include "Snake.h"
#include "PowerUp.h"
#include "Player.h"

class Board {
public:
  int height;
  int width;
  int size;
  Ladder ladders[3];
  Snake snakes[3];
  std::vector<PowerUp> powerUps;
public:
  void generate(int h, int w);
  void render(std::vector<Player> players);
  void checkForSnakeAndMove(Player* player);
};