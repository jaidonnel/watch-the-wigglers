#pragma once
#include <string>

class Player {
public:
  std::string name;
  int position;
public:
  Player();
  bool hasPowerUp(int boardSize);
  bool hasWon(int boardSize);
  void move(int numOfTiles);
};