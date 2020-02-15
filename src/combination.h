#ifndef COMBINATION_H
#define COMBINATION_H

#include "card.h"
#include <vector>
#include <algorithm> // std::sort

class Combination
{
   public:
      Combination() = default;
      ~Combination() = default;

      enum class type {
         UNDEFINED = 0,
         BOOK,
         RUN,
         PARTIAL_BOOK,
         PARTIAL_RUN
      };
      
      // Validate if the combination is valid for each type of combination
      virtual bool isValidCombination() = 0;

      // Get the type of combination
      virtual type getType() const = 0;

      // Return the cards in the combination
      std::vector<Card> getCardsInCombination();

      // Add card to combination
      void addCard(Card card);

      // Remove card from combination
      void removeCard(Card card);

      // Sort the cards in the combination
      static std::vector<Card> sortCards(std::vector<Card> cards);

      // Return copy of card at index in combination
      Card at(int index);

      // Set the extracted state of the combination
      // This is set when extracting from the hash table in CombinationFinder
      void setExtracted();

      // Check if the combination has been been extracted from the hash table in CombinationFinder
      bool isExtracted() const;

   protected:
      std::vector<Card> cards;
      bool extracted = false;
};

#endif