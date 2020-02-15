#include "card.h"


/* *********************************************************************
Function Name: Card()
Purpose: Constructor that takes in information to create a card.
Parameters:
         string number, the number of the card
         string suit, the suit of the card
         int value, the value of the card
         bool isWild, whether or not it's a wild card
Return Value: The Card object
Local Variables:
         none
Algorithm:
         1) Assign all member variables to the variables passed in
Assistance Received: none
********************************************************************* */
Card::Card(std::string number, std::string suit, int value, bool wild)
{
   this->number = number;
   this->suit = suit;
   this->value = value;
   this->wild = wild;
}

/* *********************************************************************
Function Name: Card()
Purpose: Constructor that takes in a card and round to create a card
Parameters:
         string card, 
Return Value: The Card object
Local Variables:
         string number, the first character of string card passed in
         string suit, the second character of string card passed in
Algorithm:
         1) Grab the card number by getting the first character of
            string card
         2) Grab the card suit by getting the second character of 
            string card
         3) Assign member variable string number and string suit
         4) Use the valueOfCard map to get the value of the card
            and assign member variable int value
         5) Check if the card is a wild card or joker and
            assign member variable bool wild
Assistance Received: none
********************************************************************* */
Card::Card(std::string card, int round)
{
   std::string number = card.substr(0, 1);
   std::string suit = card.substr(1, 1);
   this->number = number;
   this->suit = suit;
   this->value = this->valueOfCard[number];

   // Check if card is a wild card
   // It can't be a joker
   if (((this->valueOfCard.at(number) - WILD_CARD_OFFSET) == round) && suit != "J")
   {
      this->value = 20;
      this->wild = true;
   }

   // If it's a joker, it's value is 50 and it effectively acts as a wild card
   std::string cardString =  number + suit;
   if (cardString == "J1" || cardString == "J2" || cardString == "J3")
   {
      this->value = 50;
      this->wild = true;
   }

}

/* *********************************************************************
Function Name: getNumber()
Purpose: Return member variable string number from Card object
Parameters:
         none
Return Value: a const string that will be a string from the numbers 3-9,
   or X, J, Q, K
Local Variables:
         none
Algorithm:
         1) Return the member variable string number
Assistance Received: none
********************************************************************* */
std::string Card::getNumber() const
{
   return this->number;
}


/* *********************************************************************
Function Name: getIntNumber()
Purpose: Return the integer equivalent of member variable string number
Parameters:
         none
Return Value: a const int, which is the value of the key in map between 
string and int of card numbers
Local Variables:
         none
Algorithm:
         1) Return the value of the valueOfCard map at key which
         is the string number of the object (i.e. "Q" -> 12
Assistance Received: none
********************************************************************* */
int Card::getIntNumber() const
{
   return this->valueOfCard.at(this->number);
}

/* *********************************************************************
Function Name: getSuit()
Purpose: Return member variable string suit
Parameters:
         none
Return Value: a const string, which is the member variable string suit
Local Variables:
         none
Algorithm:
         1) Return member variable string suit
Assistance Received: none
********************************************************************* */
std::string Card::getSuit() const
{
   return this->suit;
}


/* *********************************************************************
Function Name: getValue()
Purpose: Return member variable int value
Parameters:
         none
Return Value: a const int, which is the member variable int value
Local Variables:
         none
Algorithm:
         1) Return member variable int value
Assistance Received: none
********************************************************************* */
int Card::getValue() const
{
   return this->value;
}

/* *********************************************************************
Function Name: isWild()
Purpose: Return member variable bool wild
Parameters:
         none
Return Value: a const bool, which is the member variable bool wild
Local Variables:
         none
Algorithm:
         1) Return member variable bool wild
Assistance Received: none
********************************************************************* */
bool Card::isWild() const
{
   return this->wild;
}

/* *********************************************************************
Function Name: toString()
Purpose: Return string equivalent of card i.e. "5C"
Parameters:
         none
Return Value: a const string, which is the card i.e. "5C"
Local Variables:
         none
Algorithm:
         1) Add the Card's number and suit together and returns
            the concatenated string
Assistance Received: none
********************************************************************* */
std::string Card::toString() const
{
   return this->getNumber() + this->getSuit();
}

/* *********************************************************************
Function Name: operator <<()
Purpose: Overload << operator to allow printing of cards
Parameters:
         os, a reference to output stream
         card, a reference to the Card object passed it
Return Value: Output stream object with Card's toString() method applied
Local Variables:
         none
Algorithm:
         1) Apply Card's toString() method
         2) Put the result into output stream
         3) Return output stream
Assistance Received: none
********************************************************************* */
std::ostream& operator << (std::ostream& os, const Card& card)
{
   os << card.toString();
   return os;
}

/* *********************************************************************
Function Name: operator <()
Purpose: Overload < operator to determine which card is larger
Parameters:
         other, a reference to a Card object passed in
Return Value: a const bool, which one was larger
Local Variables:
         none
Algorithm:
         1) Return whether the card passed is is less than other card
Assistance Received: none
********************************************************************* */
bool Card::operator< (const Card &other) const
{
   if (this->value == other.value)
   {
      return this->suit < other.suit;
   }
   return this->value < other.value;
}


/* *********************************************************************
Function Name: getWildCardOffset()
Purpose: Get offset of the difference between round number and number of
   a wild card. The round number + offset (2) is the number of a wild card
Parameters:
         none
Return Value: a const int, the static int member WILD_CARD_OFFSET
Local Variables:
         none
Algorithm:
         1) Return WILD_CARD_OFFSET
Assistance Received: none
********************************************************************* */
const int Card::getWildCardOffset()
{
   return WILD_CARD_OFFSET;
}