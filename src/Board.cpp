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
    ladders[i].bottom = randomInt(1, size - 1);
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
  int tileNumber = size;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (tileNumber - (width - 1) + j < 10)
        std::cout << "-";
      if ((i % 2) != 0)
        std::cout << "---" << tileNumber - (width - 1) + j << "--";
      else
        std::cout << "---" << tileNumber - j << "--";
      if (tileNumber - (width - 1) + j < 100)
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < width; j++) {
          std::cout << "|      |";
      }
      std::cout << std::endl;
    }
    tileNumber -= 5;
    std::cout << std::endl;
  }
}

void Board::checkForSnakeAndMove(Player* player) {
  for (int i = 0; i < sizeof(snakes) / sizeof(Snake); i++) {
    if (player->position == snakes[i].top) {
      std::cout << "Player position: " << player->position << "\n";
      player->position = snakes[i].bottom;
    }
  }
}