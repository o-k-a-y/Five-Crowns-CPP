#include "deck.h"
#include "card.h"
#include <string>

/* *********************************************************************
Function Name: Deck()
Purpose: Constructor for Deck that sets up the deck with all cards
Parameters:
         int round, the current round number passed it
Return Value: Deck object
Local Variables:
         none
Algorithm:
         1) Generate the deck based on the current round number
Assistance Received: none
********************************************************************* */
Deck::Deck(int round)
{
   generateDeck(round);
}

/* *********************************************************************
Function Name: Deck()
Purpose: Constructor for Deck that sets up the deck's draw pile and
discard pile. Used when loading a game save file
Parameters:
         vector<Card> drawingPile, deque<Card> discardPile
Return Value: Deck object
Local Variables:
         none
Algorithm:
         1) Set the draw pile to draw pile passed in
         2) Set the discard pile to discard pile passed in
Assistance Received: none
********************************************************************* */
Deck::Deck(std::vector<Card> drawingPile, std::deque<Card> discardPile)
{
   setDrawPile(drawingPile);
   setDiscardPile(discardPile);
}

/* *********************************************************************
Function Name: generateDeck()
Purpose: Create all cards for the deck
Parameters:
         int round, the current round number
Return Value: none
Local Variables:
         int wildCardOffset, wild card offset
         int startNumber, lowest card number (3)
         string numbers[], numbers of cards besides jokers
         string suits[], every card suit "S", "C", "D", "H", "T"
         map valueOfCard, mapping of number to int number "3" -> 3
         int numOfNumbers, number of numbers 3-K
         int numOfSuits, number of suits
Algorithm:
         1) For every number, create a card with that number and
         every suit.
         2) Create 3 jokers
         3) Repeat steps 1 and 2
Assistance Received: none
********************************************************************* */
void Deck::generateDeck(int round)
{
   // Get the wild card offset
   int wildCardOffset = Card::getWildCardOffset();

   // Cards start at the number 3
   int startNumber = 3;

   // Numbers of cards besides joker
   std::string numbers[11] = {
     "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K"
   };
   
   // Suits of cards besides joker
   std::string suits[5] = {
     "S", "C", "D", "H", "T"
   };

   // The value of each card
   std::map<std::string, int> valueOfCard =
   {
      { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 },
      { "8", 8 }, { "9", 9}, { "X", 10 }, { "J", 11 }, { "Q", 12 }, { "K", 13 }
   };

   int numOfNumbers = sizeof(numbers) / sizeof(numbers[0]);
   int numOfSuits = sizeof(suits) / sizeof(suits[0]);

   // Create all cards (two 58 card decks)
   for (int i = 0; i < 2; i++)
   {
      // Create all cards but jokers
      for (int number = 0; number < numOfNumbers; number++)
      {
         for (int suit = 0; suit < numOfSuits; suit++)
         {
            // The card is wild if the face number - 2 is the round number
            // i.e. for round 1, the wild card is 3
            Card newCard;
            if (number + startNumber - wildCardOffset == round)
            {
               newCard = Card(numbers[number], suits[suit], 20, true);
            }
            else
            {
               newCard = Card(numbers[number], suits[suit], valueOfCard[numbers[number]], false);
            }
            //std::cout << "newly generated card" << newCard.toString();
            deck.push_back(newCard);
         }
      }

      // Create the jokers
      for (int i = 1; i < 4; i++)
      {
         Card joker("J", std::to_string(i), 50, true);
         deck.push_back(joker);
      }
   }
}

/* *********************************************************************
Function Name: printDeck()
Purpose: Prints all cards in the drawing pile
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Call toString() on every card in the drawing pile
         2) Print each card
Assistance Received: none
********************************************************************* */
void Deck::printDeck()
{
   for (std::vector<Card>::const_iterator i = deck.begin(); i != deck.end(); ++i)
   {
      std::cout << i->toString() << " ";
   }
}

/* *********************************************************************
Function Name: printDiscard()
Purpose: Prints all cards in the discard pile
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Call toString() on every card in the discard pile
         2) Print each card
Assistance Received: none
********************************************************************* */
void Deck::printDiscard()
{
   for (std::deque<Card>::const_iterator i = discardPile.begin(); i != discardPile.end(); ++i)
   {
      std::cout << i->toString() << " ";
   }
}

/* *********************************************************************
Function Name: shuffleDeck()
Purpose: Randomly shuffle all cards in the deck
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Call random_shuffle on the deck from beginning to end
Assistance Received: none
********************************************************************* */
void Deck::shuffleDeck()
{
    std::random_shuffle(deck.begin(), deck.end());
}

/* *********************************************************************
Function Name: takeNCards()
Purpose: Takes N cards from the deck
Parameters:
         int n, the number of cards to take
Return Value: a vector<Card> which contains the cards drew
Local Variables:
         vector<Card> cards, the cards we will return
Algorithm:
         1) Create a vector<Card> to contain the cards to draw
         2) Loop from 0 to n
         3) Push the first card from deck to vector
         4) Delete first card from deck
         5) Return the vector of cards
Assistance Received: none
********************************************************************* */
std::vector<Card> Deck::takeNCards(int n)
{
   std::vector<Card> cards;

   // Push cards to array and delete from deck
   for (int i = 0; i < n; i++)
   {
      cards.push_back(deck.front());
      deck.erase(deck.begin(), deck.begin() + 1);
   }

   return cards;
}

/* *********************************************************************
Function Name: drawFromDeck()
Purpose: Takes a single card from the deck
Parameters:
         none
Return Value: a Card which is the card we drew from deck
Local Variables:
         Card card, the card we will draw
Algorithm:
         1) Set card to the top of the deck
         2) Erase the top of the deck
         3) Return the card
Assistance Received: none
********************************************************************* */
Card Deck::drawFromDeck()
{
   Card card = deck.at(0);
   deck.erase(deck.begin(), deck.begin() + 1);

   return card;   
}


/* *********************************************************************
Function Name: drawFromDiscard()
Purpose: Takes a single card from discard pile
Parameters:
         none
Return Value: a Card which is the card we drew from discard pile
Local Variables:
         Card card, the card we will draw
Algorithm:
         1) Set card to the top of the discard pile
         2) Erase the top of the deck
         3) Return the card
Assistance Received: none
********************************************************************* */
Card Deck::drawFromDiscard()
{
   Card card = discardPile[0];
   discardPile.pop_front();
   //discardPile.erase(discardPile.begin(), discardPile.begin() + 1);

   return card;
}

/* *********************************************************************
Function Name: addToDiscardPile()
Purpose: Adds a single card to the top of the discard pile
Parameters:
         Card card, the card we are adding to the discard pile
Return Value: none
Local Variables:
         none
Algorithm:
         1) Push card to front of discard pile
Assistance Received: none
********************************************************************* */
void Deck::addToDiscardPile(Card card)
{
   try
   {
      discardPile.push_front(card);
   }
   catch (...)
   {
      std::cout << "Can't push to discard pile\n";
      return;
   }
}

/* *********************************************************************
Function Name: setDrawPile()
Purpose: Sets the decks drawing pile
Parameters:
         vector<Card> drawPile, the drawing pile we are setting
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set Deck's deck member to drawPile
Assistance Received: none
********************************************************************* */
void Deck::setDrawPile(std::vector<Card> drawPile)
{
   this->deck = drawPile;
}

/* *********************************************************************
Function Name: setDiscardPile()
Purpose: Sets the decks discard pile
Parameters:
         vector<Card> discardPile, the discard pile we are setting
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set Deck's discardPile member to discardPile
Assistance Received: none
********************************************************************* */
void Deck::setDiscardPile(std::deque<Card> discardPile)
{
   this->discardPile = discardPile;
}


/* *********************************************************************
Function Name: isDiscardPileEmpty()
Purpose: Check if the discard pile is empty
Parameters:
         none
Return Value: a bool, whether or not the discard pile is empty
Local Variables:
         none
Algorithm:
         1) If there are no cards in the discard pile, return true
         2) If there are cards in the discard pile, return false
Assistance Received: none
********************************************************************* */
bool Deck::isDiscardPileEmpty()
{
   return this->discardPile.size() == 0 ? true : false;
}


/* *********************************************************************
Function Name: getTopOfDiscardPile()
Purpose: Get the top of the discard pile
Parameters:
         none
Return Value: a Card, the top of the discard pile
Local Variables:
         none
Algorithm:
         1) Return the top of the discard pile
Assistance Received: none
********************************************************************* */
Card Deck::getTopOfDiscardPile()
{
   return this->discardPile[0];
}

// Check if the drawing pile is empty
bool Deck::isDrawPileEmpty()
{
   return this->deck.empty();
}

/* *********************************************************************
Function Name: toString()
Purpose: Convert the deck to its string equivalent
Parameters:
         none
Return Value: a const string, the deck's string equivalent
Local Variables:
         string deckString, the drawing pile + discard pile
         string drawDeckString, the deck's drawing pile
         string discardPileString, the deck's discard pile
Algorithm:
         1) For every card in draw pile, add to drawDeckString
         2) For every card in discard pile, add to discardPileString
         3) Add drawDeckString and discardPileString to deckString
         4) Return deckString
Assistance Received: none
********************************************************************* */
std::string Deck::toString() const
{
   std::string deckString;
   std::string drawDeckString = "Draw Pile: ";
   std::string discardPileString = "Discard Pile: ";
   for (Card card : deck)
   {
      drawDeckString += card.toString() + " ";
   }

   for (Card card : discardPile)
   {
      discardPileString += card.toString() + " ";
   }
   
   deckString = drawDeckString + "\n\n" + discardPileString;
   return deckString;
}


/* *********************************************************************
Function Name: operator <<()
Purpose: Overload << operator to allow printing of deck
Parameters:
         os, a reference to output stream
         deck, a reference to the deck
Return Value: Output stream object with card's toString() method applied
Local Variables:
         none
Algorithm:
         1) Apply deck's toString() method
         2) Put the result into output stream
         3) Return output stream
Assistance Received: none
********************************************************************* */
std::ostream& operator << (std::ostream& os, const Deck& deck)
{
   os << deck.toString();
   return os;
}