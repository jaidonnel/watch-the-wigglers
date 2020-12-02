#include "Player.h"

Player::Player() {
  position = 1;
  hasPowerUp = false;
}

void Player::move(int numOfTiles, int boardSize) {
  if(position + numOfTiles > boardSize) {
    return;
  } else {
    position += numOfTiles;
  }
}