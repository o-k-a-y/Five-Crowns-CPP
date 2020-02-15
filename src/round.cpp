#include "round.h"

/* *********************************************************************
Function Name: Round()
Purpose: Constructor for Round that takes the curent round to generate
   the deck
Parameters:
         int currentRound, the current round of the game
Return Value: The Round object
Local Variables:
         Deck deck, the deck for the current round
Algorithm:
         1) Create deck by passing current roound to the Deck constructor
         2) Set the deck member variable to the deck created
         3) Shuffle the deck
Assistance Received: none
********************************************************************* */
Round::Round(int currentRound)
{
   Deck deck(currentRound);
   this->deck = deck;
   this->deck.shuffleDeck();
}

/* *********************************************************************
Function Name: Round()
Purpose: Constructor for Round that takes the drawing pile and discard pile
   to create the deck
Parameters:
         vector<Card> drawingPile, the drawing pile of the deck
         deque<Card> discardPile, the discard pile of the deck
Return Value: The Round object 
Local Variables:
         Deck deck, the deck for the current round
Algorithm:
         1) Create deck by passing current roound to the Deck constructor
         2) Set the deck member variable to the deck created
         3) Shuffle the deck
Assistance Received: none
********************************************************************* */
Round::Round(std::vector<Card> drawingPile, std::deque<Card> discardPile)
{
   Deck deck(drawingPile, discardPile);
   this->deck = deck;
}

/* *********************************************************************
Function Name: getTurnNumber()
Purpose: Returns the current turn number
Parameters:
         none
Return Value: a const int, the turn number of the round
Local Variables:
         none
Algorithm:
         1) Return the member variable turn
Assistance Received: none
********************************************************************* */
int Round::getTurnNumber() const
{
   return this->turn;
}

/* *********************************************************************
Function Name: setTurnNumber()
Purpose: Sets the current turn number
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Return the member variable turn
Assistance Received: none
********************************************************************* */
void Round::setTurnNumber(int turn)
{
   this->turn = turn;
}

/* *********************************************************************
Function Name: dealCards()
Purpose: Returns the cards(hand) each player needs to begin the round
Parameters:
         int round, the current game round
         int players, the number of players in the game
Return Value: a vector<vector<Card>>, the cards for each player
Local Variables:
         const int CARD_OFFSET, the offset from round number and cards
         vector<vector<Card>> hands, all of the players hands
Algorithm:
         1) Loop through the number of players
         2) Create each player's hand
         3) Return the hands created
Assistance Received: none
********************************************************************* */
std::vector<std::vector<Card>> Round::dealCards(int round, int players)
{
   // We deal round + 2 cards every round
   const int CARD_OFFSET = 2;

   // All the players hands
   std::vector<std::vector<Card>> hands;

   // Make each players hand
   for (int player = 0; player < players; player++)
   {
      std::vector<Card> hand = deck.takeNCards(round + CARD_OFFSET);
      hands.push_back(hand);
   }

   return hands;
}


/* *********************************************************************
Function Name: drawDeck()
Purpose: Returns the top card from the deck
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Return the top card from the deck
Assistance Received: none
********************************************************************* */
Card Round::drawDeck()
{
   return this->deck.drawFromDeck();
}

/* *********************************************************************
Function Name: drawDiscard()
Purpose: Returns the top card from the discard pile
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Return the top card from the discard pile
Assistance Received: none
********************************************************************* */
Card Round::drawDiscard()
{
   return deck.drawFromDiscard();
}

/* *********************************************************************
Function Name: getTopOfDiscardPile()
Purpose: Returns top of discard pile
Parameters:
         none
Return Value: none
Local Variables:
         Card card, the top of the discard pile
Algorithm:
         1) If deck is empty, return a blank card
         2) Otherwise return top of discard pile
Assistance Received: none
********************************************************************* */
Card Round::getTopOfDiscardPile()
{
   // If empty set to empty card
   if (this->deck.isDiscardPileEmpty())
   {
      // Return blank card
      return Card();
   }
   // Otherwise return the top of discard pile
   else
   {
      return this->deck.getTopOfDiscardPile();
   }
}

/* *********************************************************************
Function Name: isDrawingPileEmpty()
Purpose: Check if there are any cards in the discard pile
Parameters:
         none
Return Value: a bool, whether or not discard pile is empty
Local Variables:
         none
Algorithm:
         1) Return if it's empty
Assistance Received: none
********************************************************************* */
bool Round::isDrawingPileEmpty()
{
   return this->deck.isDrawPileEmpty(); 
}

/* *********************************************************************
Function Name: printDeck()
Purpose: Prints the current deck
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print the deck
Assistance Received: none
********************************************************************* */
void Round::printDeck()
{
   this->deck.printDeck();
}

/* *********************************************************************
Function Name: printDiscard()
Purpose: Prints the discard pile
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print the discard pile
Assistance Received: none
********************************************************************* */
void Round::printDiscard()
{
   this->deck.printDiscard();
}

/* *********************************************************************
Function Name: discardCard()
Purpose: Adds card to discard pile
Parameters:
         Card cardToDiscard, the card to discard
Return Value: none
Local Variables:
         none
Algorithm:
         1) Add the card to discard to the discard pile in the deck
Assistance Received: none
********************************************************************* */
void Round::discardCard(Card cardToDiscard)
{
   this->deck.addToDiscardPile(cardToDiscard);
}

/* *********************************************************************
Function Name: setDrawPile()
Purpose: Set the draw pile to the cards passed in
Parameters:
         vector<Card> drawPile, the drawing pile passed in
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set the drawing pile passed in to the deck's drawing pile
Assistance Received: none
********************************************************************* */
void Round::setDrawPile(std::vector<Card> drawPile)
{
   this->deck.setDrawPile(drawPile);
}

/* *********************************************************************
Function Name: setDiscardPile()
Purpose: Set the discard pile to the cards passed in
Parameters:
         vector<Card> discardPile, the discard pile passed in
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set the discard pile passed in to the deck's discard pile
Assistance Received: none
********************************************************************* */
void Round::setDiscardPile(std::deque<Card> discardPile)
{
   this->deck.setDiscardPile(discardPile);
}


/* *********************************************************************
Function Name: serializeDeck()
Purpose: Serialize and return the deck object to save the current game state
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Return the stringified deck
********************************************************************* */
std::string Round::serializeDeck()
{
   return this->deck.toString();
}