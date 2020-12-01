#include "Player.h"

Player::Player() {
  position = 1;
  hasPowerUp = false;
}

void Player::move(int numOfTiles) {
  position += numOfTiles;
}