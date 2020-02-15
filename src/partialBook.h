#ifndef PARTIALBOOK_H
#define PARTIALBOOK_H

#include "combination.h"

class PartialBook : public Combination
{
   public:
      PartialBook() = default;
      ~PartialBook() = default;

      // Overloaded constructor
      PartialBook(std::vector<Card> cards);

      // Validate if the book is valid
      bool isValidCombination() override;

      // Get the type of combination
      type getType() const override;

};

#endif