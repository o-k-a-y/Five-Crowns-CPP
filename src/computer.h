#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player
{
   public:
      Computer() = default;
      ~Computer() = default;

      enum class Help {
         UNDEFINED = 0,
         DRAW_HELP,
         DISCARD_HELP
      };

      virtual int chooseGameOption() override;
      virtual int move() override;
      virtual void printMenu() override;
      virtual std::pair<bool, std::string> getCardToDiscard() override;
      virtual std::string toString() const override;

      // Function Human player can call to ask for help on what moves to make
      static void help(std::vector<Card> hand, Card discardCard, Computer::Help helpType);

      // Check if we should draw from the discard pile or drawing pile
      bool shouldDrawFromDiscard();

      // Return the number of remaining cards after making combinations from a vector of cards
      int numberOfRemainingCards(std::vector<Card> hand, CombinationFinder::Order combinationOrder);

      // Return the number of single cards after making combinations from vector of cards
      int numberOfSingleCards(std::vector<Card> hand, CombinationFinder::Order combinationOrder);
};

#endif