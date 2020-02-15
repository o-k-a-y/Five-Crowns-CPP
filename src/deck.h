#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
//#include <list>
#include <algorithm>  // std::random_shuffle
#include <ctime>      // std::time
#include <cstdlib>    // std::rand, std::srand
#include <iostream>   // delete or set to debug
#include <random>     // default random engine
#include <deque>


class Deck
{
   public:
      Deck() = default;
      ~Deck() = default;

      // Constructor that takes in round number so we know what the wild card is
      Deck(int round);

      // Constructor for Deck that is used when loading a game save file
      // Sets the drawing pile and discard pile to the cards passed in
      Deck(std::vector<Card> drawingPile, std::deque<Card> discardPile);

      // So we can output deck using streams
      friend std::ostream& operator<<(std::ostream& os, const Deck& deck);

      /**
       * @brief Generate the deck of cards
       * Two 58-card decks are used which each contain:
       * 5 suits: spades, clubs, diamonds, hearts, and tridents
       * 11 cards in each suit: 3 though 10, Jack, Queen, King
       * 3 jokers
       */
      void generateDeck(int round);

      /**
       * @brief Prints the deck of cards
       */
      void printDeck();

      // Print cards in discard pile
      void printDiscard();

      /**
       * @brief shuffle the deck of cards
       */
      void shuffleDeck();

      // takes N cards from top of deck
      std::vector<Card> takeNCards(int n);

      // Returns and deletes the first card of the deck
      Card drawFromDeck();

      // Returns and deletes the first card of the discard pile
      Card drawFromDiscard();

      // Add card to top of discard pile
      void addToDiscardPile(Card card);

      // Set the draw pile to the cards passed in
      void setDrawPile(std::vector<Card> drawPile);

      // Set the discard pile to the cards passed in
      void setDiscardPile(std::deque<Card> discardPile);

      // Check if there are any cards in the discard pile
      bool isDiscardPileEmpty();

      // Get a copy of the top of the discard pile
      Card getTopOfDiscardPile();

      // Check if the drawing pile is empty
      bool isDrawPileEmpty();

      // To string function so we can output the deck
      std::string toString() const;


   private:
      std::vector<Card> deck;         // the deck of cards
      std::deque<Card> discardPile;   // the discard pile
      bool empty;                  // whether or not there are cards in draw pile
};

#endif