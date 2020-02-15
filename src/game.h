#ifndef GAME_H
#define GAME_H

#include "round.h"
#include "human.h"
#include "computer.h"
#include "gameFile.h"

#include <memory>         // smart pointers
#include <stdlib.h>         // srand, rand
#include <fstream>         // fstream for reading and writing files
#include <regex>
#include <unordered_map>   // to store value of game file


class Game
{
   public:
      /**
       * @brief Default constructor
       */
      Game();

      /** 
       * @brief Deconstructor
       */
      ~Game() = default;

      /** 
       * @brief Start the game
       */
      void startGame();


   private:
      Round round;                                 // the actual round object
      int roundNumber = 1;                           // number of round we're on
      static const int PLAYER_COUNT = 2;                   // number of players in the game
      std::shared_ptr<Player> players[2];                  // array of players
      int scores[2] = { 0 };                           // the total scores of all the players
      int playerOne;                                 // the first player to move
      int currentPlayer;                              // the player whose turn it currently is
      int turnNumber = 0;                              // curren turn number of game
      bool hasPlayerGoneOut = false;                     // whether or not a player has gone out
      int firstPlayerOfNextRound;                        // the player to go first in the next round

      int goneOutCount = 0;

      /**
       * @brief Print menu when game starts
       *
       * This menu prints the options to start a new game, load from file, or quit
       */
      void startMenu();

      /**
       * @brief Randomly choose player who starts
       */
      void setFirstPlayer();

      /**
       * @brief Return the first player in the round
       */
      int getFirstPlayer() const;

      // Gets the current player
      void setCurrentPlayer(int turn);

      // Return the game option
      std::string getStartChoice() const;

      // Starts the first round of the game
      void firstRound();

      // Deal cards to all players
      // Clear hands before dealing to make sure they have none beforehand
      void dealCards();

      // Clear players hand and discard card
      void resetPlayerCards();

      // Play the next turn of the round
      void nextTurn();

      // Play the last turn of the round
      // This is called when one player goes out and all other player have a chance to 
      // reduce the number of points they will receive by playing on more turn
      void lastTurn();

      // Update all the players score
      // The score is equal to the value of all the cards left in the player's hand
      // If a player goes out, they have a score of 0 for that round
      void updatePlayerScores();

      /**
       * @brief Starts the next game round
       */
      void nextRound();

      // Prepare the round
      // This will reset the players' gone out status,
      // set the player to play first to the first player of next round (determined when a player goes out),
      // and resets the current turn number
      void prepareRound();

      // Reset player's gone out status
      void resetPlayerStatus();

      // Continues the round when loading game save file
      void continueRound();

      // Prints info that must always be displayed on screen
      // round number
      // human hand and computer hand
      // human game score and computer game score
      // the card on top of the discard pile
      // the cards in the draw pile - although they will be visible, assume that neither player can see them.
      void printGameStats();

      // Make the move for the player
      void movePlayer();

      // Check if the deck is empty (no cards remaining in draw pile)
      bool isDeckEmpty();

      // Get the card the player is discarding
      void getCardToDiscard();

      // Ask computer player for help
      void askComputerForHelp(Computer::Help helpType);

      // Set the current players score
      void setPlayerScore(int player, int score);

      // Set the players hand to the cards passed in
      // this calls Player::addToHand() function that takes in cards and adds them to its current hand
      void setPlayerHand(int player, std::vector<Card> hand);

      // Set the draw pile to the cards passed in
      void setDrawPile(std::vector<Card> drawPile);

      // Set the discard pile to the cards passed in
      void setDiscardPile(std::deque<Card> discardPile);

      // Sets the top of the discard pile for Players
      // TEMPORARY UNTILL I CAN FIGURE OUT HOW TO MAKE TOPOFDISCARD STATIC IN PLAYER
      void setTopOfDiscard(Card topOfDiscard);

      // Parse the game file passed in
      // This is called when user entered 2 to load a game
      void loadGameFile();

      // Save the current game state. Called when use specifies they want to save the game
      void serializeGame();

      // Determine the winner of the game
      // Returns the index of the player with the highest score
      // If scores are tied, returns -1
      int determineWinner();

      // Determine if there is a tie in the game
      // A tie is if players have the same score
      bool isTie();

      // Print the winner of the game
      // Called when round 11 ends
      void printWinner();

};

#endif
