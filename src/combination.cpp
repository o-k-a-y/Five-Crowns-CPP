#include "combination.h"

/* *********************************************************************
Function Name: getCardsInCombination()
Purpose: Get the cards within the combination.
Parameters:
         none
Return Value: a vector<Card>, the Card objects within the combination
Local Variables:
         none
Algorithm:
         1) Return cards member object
Assistance Received: none
********************************************************************* */
std::vector<Card> Combination::getCardsInCombination()
{
   return this->cards;
}


/* *********************************************************************
Function Name: addCard()
Purpose: Add card to combination.
Parameters:
         a Card object we are adding to the combination.
Return Value: none
Local Variables:
         none
Algorithm:
         1) Push the card to the end of the cards vector
Assistance Received: none
********************************************************************* */
void Combination::addCard(Card card)
{
   this->cards.push_back(card);
}

/* *********************************************************************
Function Name: removeCard()
Purpose: Remove card from combination
Parameters:
         a Card object we are remove from the combination.
Return Value: none
Local Variables:
         vector<Card>iterator it, an iterator to iterate over cards
         in combination.
Algorithm:
         1) Create iterator at beginning of cards vector
         2) Loop through cards to end
         3) If the stringified card the iterator points to is equal 
         to the stringified card passed in, erase the card
Assistance Received: none
********************************************************************* */
void Combination::removeCard(Card card)
{
   std::vector<Card>::iterator it = this->cards.begin();
   while (it != this->cards.end())
   {
      if (it->toString() == card.toString())
      {
         it = this->cards.erase(it);
      }
      else
      {
         ++it;
      }
   }
}

/* *********************************************************************
Function Name: sortCards()
Purpose: Sort the cards in the combination
Parameters:
         a vector<Card>, the sorted cards passed in
Return Value: none
Local Variables:
         none
Algorithm:
         1) Call std::sort from beginning to end of cards passed in
         2) This will evaluate the > operator which is overloaded in
         Card class. We sort by numbers incrementaly and by suit
         alphabetically.
Assistance Received: none
********************************************************************* */
std::vector<Card> Combination::sortCards(std::vector<Card> cards)
{
   std::sort(cards.begin(), cards.end());

   return cards;
}


/* *********************************************************************
Function Name: at()
Purpose: Return copy of card at index in combination
Parameters:
         an int, the index of the combination we are looking for
Return Value: none
Local Variables:
         none
Algorithm:
         1) Return card at index
Assistance Received: none
********************************************************************* */
Card Combination::at(int index)
{
   return this->cards[index];
}

/* *********************************************************************
Function Name: setExtracted()
Purpose: Set the extracted state of the combination. This is set
   when extracting from the hash table in CombinationFinder
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set extracted member variable to true
Assistance Received: none
********************************************************************* */
void Combination::setExtracted()
{
   this->extracted = true;
}


/* *********************************************************************
Function Name: isExtracted()
Purpose: Check if the combination has been been extracted from the
   hash table in CombinationFinder
Parameters:
         none
Return Value: a const bool, the extracted state of the combination
Local Variables:
         none
Algorithm:
         1) Set extracted member variable to true
Assistance Received: none
********************************************************************* */
bool Combination::isExtracted() const
{
   return this->extracted;
}