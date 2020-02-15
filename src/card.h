#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <map>

class Card
{
   public:
      // Default constructor
      Card() = default;
      ~Card() = default;

      // Constructor that takes in information to create a card.
      Card(std::string number, std::string suit, int value, bool isWild);

      // Constructor that takes in a card and round to create a card
      Card(std::string card, int round);

      bool operator< (const Card &other) const;

      std::string getSuit() const;

      std::string getNumber() const;

      int getIntNumber() const;

      int getValue() const;

      bool isWild() const;

      std::string toString() const;

      static const int getWildCardOffset();

      friend std::ostream& operator<<(std::ostream& os, const Card& card);

   private:
      // card number
      std::string number = "";         

      // card suit
      std::string suit = "";               

      // card value (number of points the card is worth)
      int value = -1;                     

      // whether or not it's a wild card (or a joker since it can act as one)
      bool wild = false;                  

      // the round number + wild card offset (2) is the number of a wild card
      static const int WILD_CARD_OFFSET = 2;   
      
      // The value of each card                           
      std::map<std::string, int> valueOfCard =
      {
         { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 },
         { "8", 8 }, { "9", 9}, { "X", 10 }, { "J", 11 }, { "Q", 12 }, { "K", 13 }
      };
};


#endif