#ifndef RUN_H
#define RUN_H

#include "combination.h"

class Run : public Combination
{
   public:
      Run() = default;
      ~Run() = default;

      // Overloaded constructor
      Run(std::vector<Card> cards);

      // Validate if the run is valid
      bool isValidCombination() override;

      // Get the type of combination
      type getType() const override;
};

#endif