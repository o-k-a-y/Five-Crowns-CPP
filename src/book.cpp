#include "book.h"


/* *********************************************************************
Function Name: Book()
Purpose: Constructor that takes in a vector of cards and saves them
in combination.
Parameters:
         a vector<Card>, cards to store in member variable
Return Value: The Book object
Local Variables:
         none
Algorithm:
         1) Set set the vector of cards to the member variable cards
Assistance Received: none
********************************************************************* */
Book::Book(std::vector<Card> cards)
{
   this->cards = cards;
}

/* *********************************************************************
Function Name: isValidCombination()
Purpose: Check that the combination is valid
Parameters:
         none
Return Value: a bool, representing whether if the combination is valid
Local Variables:
         none
Algorithm:
         1) If size is less than 3, it's not a book, return false
         2) Make sure cards are sorted
         3) Get the first number of a card that is not wild
         4) If we can't find any numbers, all cards are wild, and
         it's a book
         5) Verify the remaining non-wild cards all have equal value
         6) If they do, it's a book, otherwise it's not
Assistance Received: none
********************************************************************* */
bool Book::isValidCombination()
{
   // If number of cards is less than 3, it can't ever be a book
   if (cards.size() < 3)
   {
      return false;
   }

   // Make sure cards are sorted by value
   cards = sortCards(cards);

   std::string number = "";

   // Get the first number that is not a wild card or joker
   for (Card card : cards)
   {
      if (!card.isWild())
      {
         number = card.getNumber();
         break;
      }

   }

   // If there was no cards that wasn't a wild card or joker, they are all wild cards or jokers
   // So we have a book
   if (number == "")
   {
      return true;
   }

   // Check to see if all cards that are not wild or joker has the same number as number
   for (Card card : cards)
   {
      if (!card.isWild())
      {
         if (card.getNumber() == number)
         {
            continue;
         }
         else
         {
            return false;
         }
      }
   }

   return true;
}


/* *********************************************************************
Function Name: getType()
Purpose: Get the type of combination
Parameters:
         none
Return Value: a const Combination::type enum, the type of combination
Local Variables:
         none
Algorithm:
         1) Return Combination::type::BOOK 
Assistance Received: none
********************************************************************* */
Combination::type Book::getType() const
{
   return type::BOOK;
}