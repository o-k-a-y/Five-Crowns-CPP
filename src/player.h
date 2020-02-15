#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "combinationFinder.h"
#include <vector>
#include <algorithm> // std::sort
#include <iostream>
//#include <map>

class Player
{
   public:
      Player() = default;
      ~Player() = default;

      // Choose initial game option
      virtual int chooseGameOption() = 0;

      // Make a move
      virtual int move() = 0;
      
      // Print the menu for the turn depending on Player type
      virtual void printMenu() = 0;

      // Get the card the player will be discarding and whether or not they ask for help
      virtual std::pair<bool, std::string> getCardToDiscard() = 0;

      // Return 
      virtual std::string toString() const = 0;
      
      // The move options the players can make each turn when making a move
      enum class moveOption {
         UNDEFINED = 0,
         DRAW_DECK,
         DRAW_DISCARD,
         ASK_HELP
      };

      // Outputs player name, player score, and player hand for use with serialization
      std::string serialize() const;

      // So we can output player using streams
      friend std::ostream& operator<<(std::ostream& os, const Player& deck);

      // Set the player's hand
      void setHand(std::vector<Card> cards);

      // Add single card to player hand
      void addToHand(Card card);

      // Clears the player's hand
      void clearHand();

      // Sets player's discard card to a blank card
      void resetDiscardCard();

      // Print the players current hand
      void printHand();

      // Print the top of discard pile
      void printDiscard();
      
      // Get the players current hand
      std::vector<Card> getHand() const;

      // Get the players top of discard card
      Card getDiscardCard() const;

      // Sets the current top of the discard pile
      void setTopOfDiscard(Card card);

      // Find whether or not the card exists in players hand and return the index
      // returns -1 if not found
      int findIndexInHand(std::string card);

      // Discard the card from hand and set it to the top of the discard pile
      Card discardCard(int card);

      // Get top of discard pile
      //BROKEN
      Card getCardAtIndex(int index);

      // Get player's score
      int getPlayerScore() const;

      // Set player's score
      void setPlayerScore(int score);

      // Update (add to) player's score
      void updatePlayerScore(std::vector<Card> remainingCards);

      // Sort the cards passed in
      std::vector<Card> sortCards(std::vector<Card> cards);

      // Check if player can go out
      // A player can go out if all the cards in the hand can be arranged in books and runs
      bool goOut();

      // Check if player has gone out
      bool hasGoneOut();

      // Reset player's gone out status
      void resetGoneOutStatus();

      // Returns an enum with the order we should create combinations 
      CombinationFinder::Order bestOrder(std::vector<Card> cards);

      // Display all books and runs made after going out
      void displayBooksAndRuns();

   protected:
      // The cards in the players hand
      std::vector<Card> hand;

      // The books the player made when going out
      std::vector<std::vector<Card>> books;
      
      // The runs the player made when going out
      std::vector<std::vector<Card>> runs;

      // The game options the players can make
      enum class gameOption {
         UNDEFINED = 0,
         SAVE_GAME,
         MAKE_MOVE,
         ASK_HELP,
         QUIT_GAME
      };

      // The viewable card at the top of the discard pile
      Card topOfDiscard;
      
      // The players score
      int score = 0;
      
      // Whether or not player went out
      bool goneOut = false;

      // Unique books and runs
      // Books have keys of "3" to "K" for every number
      std::map<std::string, std::vector<std::vector<Card>>> booksMap;
      // Runs have keys of "C" to "T" for every suit
      std::map<std::string, std::vector<std::vector<Card>>> runsMap;
};

#endif