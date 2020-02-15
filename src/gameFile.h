#ifndef GAMEFILE_H
#define GAMEFILE_H

#include "card.h"         // to add cards to 
#include <string>
#include <deque>         // to store discard pile
#include <vector>         // to store hands and drawing pile
#include <fstream>         // to read file
#include <unordered_map>   // to store values of the game file
#include <regex>         


class GameFile
{
   public:
      // Default GameFile constructor and destructor
      GameFile() = default;
      ~GameFile() = default;

      // Open a file and return true or false if open failed
      bool openFile();

      // Creates the keys and values for the unordered map 
      // where the key is the variable (i.e. score, hand, etc)
      // and the value is what's after the colon: (i.e. "1", "S6 S5 S4", etc)
      void parseFile();

      // Get the game round
      int getGameRound() const;

      // Get the computer score
      int getComputerScore() const;

      // Get the human score
      int getHumanScore() const;

      // Get the next player
      int getNextPlayer() const;

      // Get the computer's hand
      std::vector<Card> getComputerHand() const;

      // Get the human's hand
      std::vector<Card> getHumanHand() const;

      // Get the draw pile
      std::vector<Card> getDrawPile() const;

      // Get the discard pile
      std::deque<Card> getDiscardPile() const;

      // Saves the current game state into user specified file
      void saveGameToFile(std::string gameState);


   private:
      int gameRound;
      int computerScore;
      int humanScore;
      int nextPlayer;

      std::vector<Card> computerHand;
      std::vector<Card> humanHand;
      std::vector<Card> drawPile;

      std::deque<Card> discardPile;
      
      std::ifstream loadFile;

      std::ofstream saveFile;

      // Hashmap to store values from game file
      std::unordered_map<std::string, std::string> gameValues;

      // Ask user for filename and return name
      std::string getGameFileName();

      // Parse the integer values of the game file
      void parseInt();

      // Parse the list of cards from the game file
      void parseCards();

      // Create a vector of cards from the game file
      std::vector<Card> createVectorOfCards(std::vector<std::string> cardStrings);

      // Create a deque of cards from the game file
      std::deque<Card> createDequeOfCards(std::vector<std::string> cardStrings);
};


#endif