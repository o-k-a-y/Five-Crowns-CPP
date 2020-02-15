#ifndef BOOK_H
#define BOOK_H

#include "combination.h"

class Book : public Combination
{
   public:
      Book() = default;
      ~Book() = default;

      // Overloaded constructor
      Book(std::vector<Card> cards);

      // Validate if the book is valid
      bool isValidCombination() override;

      // Get the type of combination
      type getType() const override; 

};

#endif