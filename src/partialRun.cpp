#include "partialRun.h"


/* *********************************************************************
Function Name: PartialRun()
Purpose: Constructor for PartialRun that sets its card to the ones passed
   to the constructor
Parameters:
         vector<Card> cards, the Card objects in the PartialRun
Return Value: The PartialRun object
Local Variables:
         none
Algorithm:
         1) Set member variable cards to the ones passed in
Assistance Received: none
********************************************************************* */
PartialRun::PartialRun(std::vector<Card> cards)
{
   this->cards = cards;
}


/* *********************************************************************
Function Name: isValidCombination()
Purpose: Validate if the partial run is valid
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Check if size is 2
         2) If it's not, return false (a partial run is size 2)
         3) Otherwise make sure the difference of the two cards is 1
         4) If it's not return false (THIS IS A BUG)
         5) Otherwise return true
Assistance Received: none
********************************************************************* */
bool PartialRun::isValidCombination()
{
   // If number of cards is not 2, it's not a partial book
   if (cards.size() != 2)
   {
      return false;
   }

   int firstNumber = cards[0].getIntNumber();
   int secondNumber = cards[1].getIntNumber();

   // If the difference isn't 1
   if (abs(secondNumber - firstNumber) != 1)
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
         1) Return the enum PARTIAL_RUN
Assistance Received: none
********************************************************************* */
Combination::type PartialRun::getType() const
{
   return type::PARTIAL_RUN;
}