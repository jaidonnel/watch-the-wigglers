#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <vector>
#include <limits>
#include "structures.h"

int randomInt(int start, int end);

int randomInt(int start, int end) {
  return start + rand() % end;
};

void clearScreen() {
  std::cout << "\033[2J\033[1;1H";
}

class Board {
public:
  int height;
  int width;
  int size;
  Ladder ladders[3];
  Snake snakes[3];
  std::vector<PowerUp> powerUps;
public:
  void generate(int h, int w) {
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

  void render(std::vector<Player> players) {
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
};

// class Tile {
// public:
// };

int main() {
    srand(time(NULL));
    int numOfPlayers, boardHeight, boardWidth;
    std::string emojis[4] = {"😀", "😁", "😍" "😉"};
    std::cout << emojis[0];
    std::cout << emojis[1];
    std::cout << emojis[2];
    std::cout << emojis[3];
    std::vector<int> emojiChoices;
    std::vector<Player> players;

    std::cout << "Welcome to Watch The Wigglers." << std::endl;
    std::cout << "In this game every turn you will roll a die and move that amount of spaces." << std::endl;
    std::cout << "There are also snakes and ladders." << std::endl;
    std::cout << "If you land at the bottom of a ladder you will climb to the top of the ladder." << std::endl;
    std::cout << "If you land at the top of a snake you will slide to the bottom of the snake." << std::endl;
    std::cout << "You must land on the final square to win." << std::endl;
    std::cout << "Once you understand press enter to setup the game." << std::endl;
    std::cin.get();
    clearScreen();
    
    do {
      std::cout << "Enter the number of players (4 players maximum)" << std::endl;
      while (!(std::cin >> numOfPlayers)) { // Prevents the user from entering string characters into an int variable
        std::cout << "Enter the number of players (4 players maximum): " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    } while (numOfPlayers > 4 || numOfPlayers <= 0);

    for (int i = 1; i <= numOfPlayers; i++) {
      std::string name;
      std::cout << "Enter Player " << i << "'s name" << std::endl;
      std::cin.ignore();
      getline(std::cin, name);
      if (numOfPlayers > 1) { }
      // players.push_back({name, emojis[i-1], 0});
    }

    do {
      std::cout << "Enter the board height (Min:5, Max: 10)" << std::endl;
      while (!(std::cin >> boardHeight)) { // Prevents the user from entering string characters into an int variable
        std::cout << "Enter the board height (Min: 5, Max: 10)" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }  
    } while (boardHeight > 10 || boardHeight < 5); 
    
    do {
      std::cout << "Enter the board width (Min:5, Max: 10)" << std::endl;
      while (!(std::cin >> boardWidth)) { // Prevents the user from entering string characters into an int variable
        std::cout << "Enter the board width (Min:5, Max: 10)" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }  
    } while (boardWidth > 10 || boardWidth < 5);

    std::cout << "Let's begin" << std::endl;
    std::cin.ignore();
    std::cin.get();
    clearScreen();

    Board board;
    board.generate(boardHeight, boardWidth);
    board.render(players);

    std::cin.get();
    return 0;
}