#ifndef ROUND_H
#define ROUND_H

#include "deck.h"

class Round
{
   public:
      Round() = default;
      ~Round() = default;

      Round(int currentRound);

      // Constructor for Round that is used when loading a game save file
      Round(std::vector<Card> drawingPile, std::deque<Card> discardPile);

      // Get the turn number
      int getTurnNumber() const;

      // Set the turn number
      void setTurnNumber(int turn);

      // Deal cards to players
      std::vector<std::vector<Card>> dealCards(int round, int players); 

      // Take top of deck pile
      Card drawDeck();

      // Take top of discard pile
      Card drawDiscard();

      // Return top of discard pile
      Card getTopOfDiscardPile();

      // Check if there are any cards in the drawing pile
      bool isDrawingPileEmpty();

      // Print current deck
      void printDeck();

      // Print the discard pile
      void printDiscard();

      // Add card to discard pile
      void discardCard(Card cardToDiscard);

      // Set the draw pile to the cards passed in
      void setDrawPile(std::vector<Card> drawPile);

      // Set the discard pile to the cards passed in
      void setDiscardPile(std::deque<Card> discardPile);

      // Serialize and return the deck object to save the current game state
      std::string serializeDeck();

   private:
      Deck deck;                  // the full deck
      int turn = 0;               // the current turn of the round we're on
};

#endif