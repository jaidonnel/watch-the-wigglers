#include "Player.h"

Player::Player() {
  position = 1;
}

bool Player::hasPowerUp(int boardSize) {
  return position == boardSize;
}

void Player::move(int numOfTiles) {
  position += numOfTiles;
}