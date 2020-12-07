#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <vector>
#include <limits>
#include "Board.h"

int randomInt(int start, int end);
int rollDice(int numOfDice);

int randomInt(int start, int end) {
  return start + rand() % (( end + 1 ) - start);
}

int rollDice(int numOfDice) {
  int diceRoll = 0;
  for (int i = 0; i < numOfDice; i++)
    diceRoll += randomInt(1, 6);
  return diceRoll;
}

void clearScreen() {
  std::cout << "\033[2J\033[1;1H";
}

void Log(const char* message) {
  std::cout << message << std::endl;
}

void getIntegerInRange(int variable, int min, int max, const char* message) {
  // Prompts the user using the message parameter and ensures that the value entered is 
  // within the range of the min and max parameters
  do {
    Log(message);
    while (!(std::cin >> variable)) { // Prevents the user from entering string characters into an int variable
      Log(message);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while (variable < min || variable > max );
}

int main() {
  srand(time(NULL));
  int numOfPlayers, boardHeight, boardWidth;
  std::vector<Player> players;

  //Explanation of Game
  std::cout << "Welcome to Watch The Wigglers." << std::endl;
  std::cout << "In this game every turn you will roll a die and move that amount of spaces." << std::endl;
  std::cout << "There are also snakes and ladders." << std::endl;
  std::cout << "If you land at the bottom of a ladder you will climb to the top of the ladder." << std::endl;
  std::cout << "If you land at the top of a snake you will slide to the bottom of the snake." << std::endl;
  std::cout << "You must land on the final square to win." << std::endl;
  std::cout << "Once you understand press enter to setup the game." << std::endl;
  std::cin.get();
  clearScreen();
  
  getIntegerInRange(numOfPlayers, 1, 4, "Enter the number of players (4 players maximum)");

  for (int i = 1; i <= numOfPlayers; i++) {
    std::string name;
    std::cout << "Enter Player " << i << "'s name" << std::endl;
    std::cin.ignore();
    getline(std::cin, name);
    Player player;
    player.name = name;
    players.push_back(player);
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

  bool isPlaying = true;
  std::string userInput;
  while (isPlaying) {
    for (int i = 0; i < numOfPlayers; i++) {
      std::cout << "It is player " << i+1 << "'s turn.\nThey are at tile " << players[i].position << "\nEnter \"ROLL\" to roll or \"EXIT\" to exit\n";
      std::cout << "Snakes\n";
      std::cout << "Snake1 Top: " << board.snakes[0].top << "\tSnake1 Bottom:" << board.snakes[0].bottom << std::endl;
      std::cout << "Snake2 Top: " << board.snakes[1].top << "\tSnake2 Bottom:" << board.snakes[1].bottom << std::endl;
      std::cout << "Snake3 Top: " << board.snakes[2].top << "\tSnake3 Bottom:" << board.snakes[2].bottom << std::endl;
      std::cout << "Ladders\n";
      std::cout << "Ladder1 Top: " << board.ladders[0].top << "\tLadder1 Bottom:" << board.ladders[0].bottom << std::endl;
      std::cout << "Ladder2 Top: " << board.ladders[1].top << "\tLadder2 Bottom:" << board.ladders[1].bottom << std::endl;
      std::cout << "Ladder3 Top: " << board.ladders[2].top << "\tLadder3 Bottom:" << board.ladders[2].bottom << std::endl;  
      std::cout << "Power Ups\n";
      for (int j = 0; j < board.powerUps.size(); j++) {
        std::cout << "Power Up" << j+1 << ": " << board.powerUps[j].position << "\n";
      }
      std::cin >> userInput;

      if (userInput == "ROLL") {
        int diceRoll;
        if (players[i].hasPowerUp) {
          diceRoll = rollDice(2);
        } else {
          diceRoll = rollDice(1);
        }
        players[i].move(diceRoll, board.size);
        clearScreen();
        board.render(players);
        board.checkForSnakeAndMove(&players[i]);
        board.checkForLadderAndMove(&players[i]);
        board.checkForPowerUp(&players[i]);
        board.checkForWin(&players[i]);
        if (players[i].won) {
          std::cout << "Player " << i+1 << " won. Congrats " << players[i].name << "!\n";
          isPlaying = false;
        }
        std::cout << players[i].name << " rolled a " << diceRoll << "\nThey are now at tile " << players[i].position << "\n";
      } else if (userInput == "EXIT") {
        std::cout << "Exiting. Thank you for playing!";
        isPlaying = false;
      }
      else {
        std::cout << "Please enter either ROLL or EXIT\n";
      }
    }
  }
  std::cin.get();
  return 0;
}