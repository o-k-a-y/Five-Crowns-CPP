#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player
{
   public:
      Human() = default;
      ~Human() = default;

      virtual int chooseGameOption() override;
      virtual int move() override;
      virtual void printMenu() override;
      virtual std::pair<bool, std::string> getCardToDiscard() override;
      virtual std::string toString() const override;

      // Prints the available move options for human players
      // 1. Draw from draw pile
      // 2. Draw from discard pile
      void printMoveOption();

      // Changes the card the user enters to be in all capital letters
      std::string cardInputToUppercase(std::string card);
};

#endif