#include "partialBook.h"

/* *********************************************************************
Function Name: PartialBook()
Purpose: Constructor for PartialBook that sets its card to the ones passed
   to the constructor
Parameters:
         vector<Card> cards, the Card objects in the PartialBook
Return Value: The PartialBook object
Local Variables:
         none
Algorithm:
         1) Set member variable cards to the ones passed in
Assistance Received: none
********************************************************************* */
PartialBook::PartialBook(std::vector<Card> cards)
{
   this->cards = cards;
}

/* *********************************************************************
Function Name: isValidCombination()
Purpose: Validate if the partial book is valid
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Check if size is 2
         2) If it's not, return false (a partial book is size 2)
         3) Otherwise it's a partial book, return true
Assistance Received: none
********************************************************************* */
bool PartialBook::isValidCombination()
{
   // If number of cards is not 2, it's not a partial book
   if (cards.size() != 2)
   {
      return false;
   }

   return true;
}

/* *********************************************************************
Function Name: getType()
Purpose: Get the type of combination
Parameters:
         none
Return Value: a const Combination::type, an enum denoting the type of
   combination
Local Variables:
         none
Algorithm:
         1) Return the enum PARTIAL_BOOK
Assistance Received: none
********************************************************************* */
Combination::type PartialBook::getType() const
{
   return type::PARTIAL_BOOK;
}