#ifndef PARTIALRUN_H
#define PARTIALRUN_H

#include "combination.h"

class PartialRun : public Combination
{
public:
   PartialRun() = default;
   ~PartialRun() = default;

   // Overloaded constructor
   PartialRun(std::vector<Card> cards);

   // Validate if the book is valid
   bool isValidCombination() override;

   // Get the type of combination
   type getType() const override;

};

#endif