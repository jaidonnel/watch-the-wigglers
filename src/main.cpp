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

void getIntegerInRange(int* variable, int min, int max, const char* message) {
  // Prompts the user using the message parameter and ensures that the value entered is 
  // within the range of the min and max parameters
  do {
    std::cout << message << std::endl;
    while (!(std::cin >> *variable)) { // Prevents the user from entering string characters into an int variable
      std::cout << message << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while (*variable < min || *variable > max );
}

int main() {
  srand(time(NULL));
  int numOfPlayers, boardHeight, boardWidth;
  std::vector<Player> players;

  //Explanation of Game
  std::cout << "Welcome to Watch The Wigglers.\n";
  std::cout << "In this game every turn you will roll a die and move that amount of spaces.\n";
  std::cout << "There are also snakes and ladders.\n";
  std::cout << "If you land at the bottom of a ladder you will climb to the top of the ladder.\n";
  std::cout << "If you land at the top of a snake you will slide to the bottom of the snake.\n";
  std::cout << "You must land on the final square to win.\n";
  std::cout << "Once you understand press enter to setup the game.\n";
  std::cin.get();
  clearScreen();

  std::string configurationType;
  
  while (1) {
    std::cout << "Enter your configuration type. Enter CUSTOM for custom settings or DEFAULT to go with the default configuration\n";
    std::cin >> configurationType;

    if (configurationType == "CUSTOM")
    {
      getIntegerInRange(&numOfPlayers, 1, 4, "Enter the number of players (4 players maximum)");
      for (int i = 1; i <= numOfPlayers; i++) {
        std::string name;
        std::cout << "Enter Player " << i << "'s name\n";
        std::cin.ignore();
        getline(std::cin, name);
        Player player;
        player.name = name;
        players.push_back(player);
      }
      getIntegerInRange(&boardHeight, 5, 10, "Enter the board height (Min:5, Max: 10)");
      getIntegerInRange(&boardWidth, 5, 10, "Enter the board width (Min:5, Max: 10)");
      break;
    } 
    else if (configurationType == "DEFAULT") 
    {
      numOfPlayers = 1;
      Player player;
      player.name = "Foo";
      players.push_back(player);
      boardHeight = 5;
      boardWidth = 5;
      break;
    }
    else if (configurationType == "DEFAULT2")
    {
      numOfPlayers = 2;
      Player player;
      player.name = "Foo1";
      players.push_back(player);
      player.name = "Foo2";
      players.push_back(player);
      boardHeight = 5;
      boardWidth = 5;
      break;
    }
    else if (configurationType == "DEBUG")
    {
      Player player;
      player.name = "DEBUG";
      players.push_back(player);
      numOfPlayers = 1;
      boardHeight = 5;
      boardWidth = 5;
      break;
    }
    else
    {
      std::cout << "Enter a valid configuration type\n";
    }
  }

  std::cout << "Let's begin\n";
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
      Player* player = &players[i];
      std::cout << "It is player " << i+1 << "'s turn.\nThey are at tile " << player->position << "\nEnter \"ROLL\" to roll or \"EXIT\" to exit\n";
      std::cout << "Snakes\n";
      std::cout << "Snake1 Top: " << board.snakes[0].top << "\tSnake1 Bottom:" << board.snakes[0].bottom << "\n";
      std::cout << "Snake2 Top: " << board.snakes[1].top << "\tSnake2 Bottom:" << board.snakes[1].bottom << "\n";
      std::cout << "Snake3 Top: " << board.snakes[2].top << "\tSnake3 Bottom:" << board.snakes[2].bottom << "\n";
      std::cout << "Ladders\n";
      std::cout << "Ladder1 Top: " << board.ladders[0].top << "\tLadder1 Bottom:" << board.ladders[0].bottom << "\n";
      std::cout << "Ladder2 Top: " << board.ladders[1].top << "\tLadder2 Bottom:" << board.ladders[1].bottom << "\n";
      std::cout << "Ladder3 Top: " << board.ladders[2].top << "\tLadder3 Bottom:" << board.ladders[2].bottom << "\n";  
      std::cout << "Power Ups\n";
      for (int j = 0; j < board.powerUps.size(); j++) {
        std::cout << "Power Up" << j+1 << ": " << board.powerUps[j].position << "\n";
      }
      getline(std::cin, userInput);
      std::string command = userInput.substr(0, userInput.find_first_of(" "));

      if (command == "ROLL")
      {
        int diceRoll;
        if (player->hasPowerUp)
          diceRoll = rollDice(2);
        else
          diceRoll = rollDice(1);
        player->move(diceRoll, board.size);
        clearScreen();
        board.render(players);
        board.checkForSnakeAndMove(player);
        board.checkForLadderAndMove(player);
        board.checkForPowerUp(player);
        board.checkForWin(player);
        if (player->won) {
          std::cout << "Player " << i+1 << " won. Congrats " << player->name << "!\n";
          isPlaying = false;
        }
        std::cout << player->name << " rolled a " << diceRoll << "\nThey are now at tile " << player->position << "\n";
      }
      #ifdef DEBUG
      else if (command == "MOVE")
      {
        if (userInput.find_first_of(" ") != std::string::npos) {
          int parameter = std::stoi(userInput.substr(userInput.find_first_of(" ")));
          player->move(parameter, board.size);
        } else {
          std::cout << "Command was entered incorrectly\n";
        }
      }
      #endif
      else if (command == "EXIT")
      {
        std::cout << "Exiting. Thank you for playing!";
        isPlaying = false;
      }
      else
      {
        std::cout << "Please enter either ROLL or EXIT\n";
      }
    }
  }
  std::cin.get();
  return 0;
}