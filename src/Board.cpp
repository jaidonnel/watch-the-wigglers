#include <iostream>
#include "Board.h"

int randomInt(int start, int end);

void Board::generate(int h, int w) {
  height = h;
  width = w;
  size = height * width;
  int numOfPowerUps = size / 10;

  // Generate Ladders
  for (int i = 0; i < sizeof(ladders) / sizeof(Ladder); i++) {
    ladders[i].bottom = randomInt(2, size - 1);
    ladders[i].top = randomInt(ladders[i].bottom + 1, size);
  }

  // Generate Snakes
  for (int i = 0; i < sizeof(snakes) / sizeof(Snake); i++) {
    snakes[i].top = randomInt(1, size - 1);
    snakes[i].bottom = randomInt(1, snakes[i].top);  
  }

  //  Generate Powers Ups
  powerUps.push_back({randomInt(width+1, width*2)});
  if (numOfPowerUps > 1) {
    for (int i = 1; i < numOfPowerUps; i++)
      powerUps.push_back({randomInt(powerUps[0].position + 1, size - width)});
  }
}

void Board::render(std::vector<Player> players) {
  /*
  This method will render the game board to the screen.
  The board adheres to the following rules:
    * The board is rendered from top to bottom, left to right
      due to the nature of the console
    * The first tile of the board (1) must always be in the
      bottom left corner
    * The board must zig-zag such that the highest numbered
      tile should be below the lowest numbered tile in the
      row above
    * Each adjacent tile in a column should differ by
      w+(w-1)-((r-1)×2) where w is the board's width and
      r is the row number
    * The final tile of the board (board height × board width) must
      be the first tile from the left in the row if:
      * The board width and board height are both even numbers
      * The board width is an odd number and the board height is an even number
    * The final tile of the board (board height × board width) must
      be the last tile from the left in the row if:
      * The board width and board height are both odd numbers
      * The board width is an even number and the board height is an odd number
  */
  int num = size;
  int tileNumber;
  bool startOnLeft;

  if (
    (width % 2) == 0 && (height % 2) == 0 ||
    (width % 2) != 0 && (height % 2) == 0
  ) {
    startOnLeft = true;
  } else if (
    (width % 2) != 0 && (height % 2) != 0 ||
    (width % 2) == 0 && (height % 2) != 0
  ) {
    startOnLeft = false;
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << "----";
      if (startOnLeft)
        tileNumber = num - j;
      else
        tileNumber = ((num - width)+1) + j;
      std::cout << tileNumber;
      if (tileNumber < 10)
        std::cout << "---";
      else
        std::cout << "--";
    }
    std::cout << "-\n";

    for (int i = 0; i < 3; i++) {
        std::cout << "|";
      for (int j = 0; j < width; j++) {
        std::cout << "       ";
        std::cout << "|";
      }
      std::cout << '\n';
    }

    num -= width;
    startOnLeft = !startOnLeft;
  }
}

void Board::checkForSnakeAndMove(Player* player) {
  for (int i = 0; i < sizeof(snakes) / sizeof(Snake); i++) {
    if (player->position == snakes[i].top) {
      player->position = snakes[i].bottom;
      std::cout << "Oops! You hit a snake! You are now at tile " << player->position << "\n";
    }
  }
}

void Board::checkForLadderAndMove(Player* player) {
  for (int i = 0; i < sizeof(ladders) / sizeof(Ladder); i++) {
    if (player->position == ladders[i].bottom) {
      player->position = ladders[i].top;
      std::cout << "Yay! You hit a ladder! You are now at tile " << player->position << "\n";
    }
  }
}

void Board::checkForPowerUp(Player* player) {
  for (int i = 0; i < sizeof(powerUps) / sizeof(PowerUp); i++) {
    if (player->position == powerUps[i].position) {
      player->hasPowerUp = true;
      return;
    } else {
      player->hasPowerUp = false;
    }
  }
}

void Board::checkForWin(Player* player) {
  if (player->position == size) {
    player->won = true;
  } else {
    player->won = false;
  }
}