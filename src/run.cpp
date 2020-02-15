#include "run.h"


/* *********************************************************************
Function Name: Run()
Purpose: Constructor for Run that sets its card to the ones passed
   to the constructor
Parameters:
         vector<Card> cards, the Card objects in the Run
Return Value: The Run object
Local Variables:
         none
Algorithm:
         1) Set member variable cards to the ones passed in
Assistance Received: none
********************************************************************* */
Run::Run(std::vector<Card> cards)
{
   this->cards = cards;
}

/* *********************************************************************
Function Name: isValidCombination()
Purpose: Validate if the run is valid
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Check if size is less than 3 
         2) If it's not, return false (a run is at least 3 cards)
         3) Otherwise it's a partial book, return true
Assistance Received: none
********************************************************************* */
bool Run::isValidCombination()
{
   // TODO
   if (this->cards.size() < 3)
   {
      return false;
   }
   
   // Make sure next number is one higher than previous
   for (size_t i = 1; i < this->cards.size(); i++)
   {
      int num = cards[i - 1].getIntNumber();
      int next = cards[i].getIntNumber();

      if ((next - num) != 1)
      {
         return false;
      }
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
         1) Return the enum RUN
Assistance Received: none
********************************************************************* */
Combination::type Run::getType() const
{
   return type::RUN;
}
