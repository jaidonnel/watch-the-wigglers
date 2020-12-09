#pragma once
#include <string>

class Player {
public:
  std::string name;
  int position;
  bool hasPowerUp, won;
public:
  Player();
  void move(int numOfTiles, int boardSize);
  void moveTo(int numOfTiles, int boardSize);
};