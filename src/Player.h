#pragma once
#include <string>

class Player {
public:
  std::string name;
  int position;
  bool hasPowerUp;
public:
  Player();
  bool hasWon(int boardSize);
  void move(int numOfTiles);
};