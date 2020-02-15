#include "combinationFinder.h"

/* *********************************************************************
Function Name: CombinationFinder()
Purpose: Constructor that takes in a vector of cards to analyze for
   combinations. 
hash table in CombinationFinder
Parameters:
         a vector<Card>, cards to analyze for books and runs, as well
         as remaining cards after analysis
Return Value: The CombinationFinder object
Local Variables:
         none
Algorithm:
         1) Initialize maps: index of suit, index of number, 
         number of index, suit of index, and value of card
         2) Set vector of cards to member variable
         3) Separate wild cards from jokers to their own vectors
         4) Populate the table with non-wild cards
Assistance Received: none
********************************************************************* */
CombinationFinder::CombinationFinder(std::vector<Card> cards)
{
   // Initialize maps that map indices to strings
   initializeMaps();

   // Store cards to member variable
   this->cards = cards;

   // Separate wild cards and jokers
   separateWildCards();

   // Add each non-wild non-joker to table
   for (Card card : this->cards)
   {
      addCardToTable(card);
      //printTable();
   }

}

/* *********************************************************************
Function Name: findCombinations()
Purpose: Find all combinations of the cards passed into constructor
   hash table in CombinationFinder
Parameters:
         Order combinationOrder, an enum denoting the order
         in which to make combinations (books or runs first)
Return Value: none
Local Variables:
         none
Algorithm:
         1) Check books first if that's the Order type
         2) Check runs first if that's the Order type
         3) Create books and runs from hash table and set each 
         combination's status in hash table to be extracted
         4) Create books and runs using partial books and partial 
         runs from hash table and wild cards. Set each combination's
         status in hash table to be extracted
         5) Push single cards to their own vector
         6) Create books and runs from single cards and wild cards
         7) Move left over wild cards to existing combination
         8) If there are no existing combinations, and there are at
         least 3 wild cards, make a book with them
         9) Combine the remaining cards not used for any combinations
         and push to the member variable remainingCards (vector<Card>)
Assistance Received: none
********************************************************************* */
void CombinationFinder::findCombinations(Order combinationOrder)
{
   // Make books first
   if (combinationOrder == Order::BOOKS_FIRST)
   {
      // Find books
      findBooks();

      // Find runs
      findRuns();
   }
   else if (combinationOrder == Order::RUNS_FIRST)
   {
      // Find runs
      findRuns();

      // Find books
      findBooks();
   }

   // Create books and runs from cards in table
   extractBooksAndRunsFromHashMap();

   // Create books and runs from partial combinations and wild cards
   createCombinationsFromPartialCombinations();

   // Move remaining cards in the table to singleCards vector
   extractRemainingCardsFromTable();

   // Create books and runs from single cards and wild cards
   createCombinationsFromSingleCards();

   // If there are left over wild cards, add them to an existing combination
   if (!this->wildCards.empty())
   {
      if (!this->books.empty())
      {
         addWildCardsCompleteCombinations(Combination::type::BOOK);
      }
      else if (!this->runs.empty())
      {
         addWildCardsCompleteCombinations(Combination::type::RUN);
      }
      // If all cards are wild
      else if (this->wildCards.size() >= 3)
      {
         std::vector<Card> wildBook = this->wildCards;
         
         this->wildCards.empty();
         this->books.push_back(wildBook);
      }
   }

   // Combine the remaining cards (single, partial, and wild cards not used)
   combineRemainingCards();
}


/* *********************************************************************
Function Name: addCardToTable()
Purpose: Add card to the table; increments the index in the table of
   the cards's suit and number
Parameters:
         Card card, the card to add to the table
Return Value: none
Local Variables:
         string suit, the suit of the card passed in
         string number, the number of the card passed in
Algorithm:
         1) Retrieve the cards suit
         2) Retrieve the cards number
         3) Incremement the table at position [suit][number]
Assistance Received: none
********************************************************************* */
inline void CombinationFinder::addCardToTable(Card card)
{
   std::string suit = card.getSuit();
   std::string number = card.getNumber();

   this->table[this->indexOfSuit[suit]][this->indexOfNumber[number]]++;
}

/* *********************************************************************
Function Name: separateWildCards()
Purpose: Remove wild cards and jokers from the cards and push to 
   separate vector
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through each card in member variable cards
         2) If that card is wild, push to member variable wildCards vector
         3) Loop through each card in member variable cards
         4) If that card is wild, delete it from cards vector
Assistance Received: none
********************************************************************* */
void CombinationFinder::separateWildCards()
{
   // Push all wild cards to new vector
   for (Card card : this->cards)
   {
      if (card.isWild())
      {
         this->wildCards.push_back(card);
      }
   }

   // Delete all wild cards from hand
   std::vector<Card>::iterator it = this->cards.begin();
   while (it != this->cards.end())
   {
      if (it->isWild())
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
Function Name: populateTheTable()
Purpose: Populate the table with non-wild cards
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through each card in member variable cards
         2) Add that card to the table
Assistance Received: none
********************************************************************* */
// Populate the table with non-wild cards
void CombinationFinder::populateTheTable()
{
   // Add each non-wild non-joker to table
   for (Card card : this->cards)
   {
      addCardToTable(card);
   }
}

/* *********************************************************************
Function Name: printTable()
Purpose: Print current state of the table
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print all numbers a card can have (3 to K)
         2) Loop through all suits
         3) Print the suit (S, C, D, H, or T) at index
         4) Loop through all numbers
         5) Print the value of the table at [suit][number]
Assistance Received: none
********************************************************************* */
void CombinationFinder::printTable()
{
   std::cout << "   ";
   for (std::pair<int, std::string> key : this->numberOfIndex)
   {
      std::cout << key.second << " ";
   }

   std::cout << "\n";

   for (int suit = 0; suit < this->SUITS; suit++)
   {
      std::cout << this->suitOfIndex[suit] << " ";
      std::cout << "|";
      for (int number = 0; number < this->NUMBERS; number++)
      {
         std::cout << this->table[suit][number] << "|";
      }
      std::cout << "\n";
   }
}

/* *********************************************************************
Function Name: initializeMaps()
Purpose: Initialize maps that map strings to indices, and values of cards
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Initialize indexOfSuit to the corresponding table index 
            of each suit ("S,C,D,H,T" -> 0,1,2,3,4)
         2) Initialize indexOfNumber to the corresponding table index 
            of each number ("3,4,5,6,7,8,9,X,J,Q,K" -> 0,1,...,10)     
         3) Initialize suitOfIndex to the corresponding suit string 
            for the index of table (0,1,2,3,4 -> "S,C,D,H,T")
         4) Initialize suitOfIndex to each index of the number
            (0,1...10)->"3,4,5,6,7,8,9,X,J,Q,K")
         5) Initialize valueOfCard to the corresponding value of 
            each number for a card
Assistance Received: none
********************************************************************* */
void CombinationFinder::initializeMaps()
{
   // The corresponding table index of each suit
   this->indexOfSuit = {
      { "S", 0 }, { "C", 1 }, { "D", 2 }, { "H", 3 }, { "T", 4 }
   };

   // The corresponding table index of each number                  
   this->indexOfNumber =
   {
      { "3", 0 }, { "4", 1 }, { "5", 2 }, { "6", 3 }, { "7", 4 },
      { "8", 5 }, { "9", 6 }, { "X", 7 }, { "J", 8 }, { "Q", 9 }, { "K", 10 }
   };

   // The corresponding suit string for the index of table (i.e. "D")
   this->suitOfIndex =
   {
      { 0, "S" }, { 1, "C" }, { 2, "D" }, { 3, "H"}, {4, "T"}
   };

   // The corresponding number string for the index of table (i.e. "5")
   this->numberOfIndex =
   {
      { 0, "3" }, { 1, "4" }, { 2, "5" }, { 3, "6" }, { 4, "7" },
      { 5, "8" }, { 6, "9" }, { 7, "X" }, { 8, "J" }, { 9, "Q" }, { 10, "K" }
   };

   // The corresponding value of each number for a card
   this->valueOfCard = 
   {
      { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 },
      { "8", 8 }, { "9", 9}, { "X", 10 }, { "J", 11 }, { "Q", 12 }, { "K", 13 }
   };
}

/* *********************************************************************
Function Name: createCardFromTableIndex()
Purpose: Create a card object from the current point (index) in the table
Parameters:
         int suitIndex, index of the suit
         int numberIndex, index of the number
Return Value: a Card object, created from the indices
Local Variables:
         string cardNumber, the number of the card to make
         string cardSuit, the suit of the card to make
         int cardValue, the value of the card to make
Algorithm:
         1) Get the card's number from looking up the value from 
            numberOfIndex map with numberIndex as the key
         2) Get the card's suit from looking up the value from
            suitOfIndex map with suitIndex as the key
         3) Get the card's value from looking up the value from
            valueOfCard map with the card's number as the key
         4) Create and return a Card object, passing the card's number,
            suit, value, and false (it's not wild), to the constructor
Assistance Received: none
********************************************************************* */
Card CombinationFinder::createCardFromTableIndex(int suitIndex, int numberIndex)
{
   std::string cardNumber = numberOfIndex[numberIndex];
   std::string cardSuit = suitOfIndex[suitIndex];
   int cardValue = valueOfCard[cardNumber];

   // The card in the table will never be wild since we 
   // separate wild cards before we insert into it
   return Card(cardNumber, cardSuit, cardValue, false);
}

/* *********************************************************************
Function Name: subtractCardsFromTable()
Purpose: Remove the given cards from the table. In other words, 
   subtract the amount of cards existing in the table since they were used 
   for a combination of any type
Parameters:
         vector<Card> cards, the cards to substract
Return Value: none
Local Variables:
         string suit, the card's suit
         string number, the card's number
         int suitIndex, the index of the card's suit in the table
         int numberIndex, the index of the card's number in the table
Algorithm:
         1) Loop through the cards passed in
         2) Get the card's suit
         3) Get the card's number
         4) Get the index of the suit of the card in the indexOfSuit map
         5) Get the index of the number of the card in the indexOfNumber map
         6) Subtract 1 from the table at [suit][number]
Assistance Received: none
********************************************************************* */
void CombinationFinder::subtractCardsFromTable(std::vector<Card> cards)
{
   for (Card card : cards)
   {
      std::string suit = card.getSuit();
      std::string number = card.getNumber();
      
      int suitIndex = this->indexOfSuit[suit];
      int numberIndex = this->indexOfNumber[number];

      // Subtract one from the table
      // If the card was "3S" this would subtract 1 from [0][0] 
      // Since "3" is the first index of numbers and "S" is the first index of suits
      this->table[suitIndex][numberIndex]--;
   }
}

/* *********************************************************************
Function Name: isCardInCombination()
Purpose: Check if a card is currently being used for a combination
Parameters:
         Card card, the card we are checking
Return Value: true if the card is in the combination, false otherwise
Local Variables:
         string suit, the card's suit
         string number, the card's number
         int suitIndex, the index of the card's suit in the table
         int numberIndex, the index of the card's number in the table
Algorithm:
         1) Loop through the cards passed in
         2) Get the card's suit
         3) Get the card's number
         4) Get the index of the suit of the card in the indexOfSuit map
         5) Get the index of the number of the card in the indexOfNumber map
         6) Subtract 1 from the table at [suit][number]
Assistance Received: none
********************************************************************* */
bool CombinationFinder::isCardInCombination(Card card)
{
   std::string key = card.toString();

   // If card exists and size is not 0
   if (completeCombinations.find(key) != completeCombinations.end() && completeCombinations[key].size() != 0)
   {
      return true;
   }

   return false;
}

/* *********************************************************************
Function Name: canRemoveFromCombination()
Purpose: Check if removing a card invalidates a combination
Parameters:
         Card card, the card we are seeing if we can remove from a
         combination
Return Value: a tuple<bool, int, int>, containing whether or not you can
   remove the card from a combination, the index of the first combination
   you can remove it from, and the index of the card in the combination.
   If no such card exists, it returns a tuple containing <false, -1, -1>
Local Variables:
         string cardString, the stringified card
         vector<shared_ptr<Combination>> completeCombos, the complete
            combinations the card is part of
         int indexOfCombination, the index of the complete combination
         Combination::type combinationType, an enum describing the type
            of combination
         vector<Card> cards, the cards in the combination
         int indexOfCard, the index of the card in the combination
         shared_ptr<Combination> book, the Book object made from the 
            combination after the card is removed
         shared_ptr<Combination> run, the Run object made from the 
            combination after the card is removed
Algorithm:
         1) Get the string of the card
         2) Get all the complete combinations the card is in
         3) Set indexOfCombination to 0
         4) Loop through each of those combinations and increment 
            indexOfCombination each loop
         5) Get the type of combination
         6) Make a vector of card from the cards in the combination
         7) Get the index of the card in the combination
         8) Remove the card from the vector of cards
         9) Make a new combination by checking the type of combination
            and passing the vector of cards to the respective combination
            constructor
         10) Check if the new combination is valid
         11) If it is, return a tuple containing true, the index of the
            combination, and the index of the card in the combination
         12) Otherwise, return a tuple containing <false, -1, -1>
Assistance Received: none
********************************************************************* */
std::tuple<bool, int, int> CombinationFinder::canRemoveFromCombination(Card card)
{
   // The stringified card
   std::string cardString = card.toString();

   // All of the complete combinations where the combination contains the card
   std::vector<std::shared_ptr<Combination>> completeCombos = completeCombinations[cardString];

   // Loop through each complete combination the card is in
   int indexOfCombination = 0;
   for (auto combination : completeCombos)
   {
      // Get type of combination
      Combination::type combinationType = combination->getType();

      // Get the cards in the combination
      std::vector<Card> cards = combination->getCardsInCombination();
      
      // The index of the card
      int indexOfCard = findIndexOfCard(cardString, cards);

      // Remove card from combination
      removeCardFromVectorOfCards(indexOfCard, cards);

      // Check the type of combination
      if (combinationType == Combination::type::BOOK)
      {
         // Create book from the cards and validate it
         std::shared_ptr<Combination> book = std::shared_ptr<Combination>(new Book(cards));
         
         if (book->isValidCombination())
         {
            return std::make_tuple(true, indexOfCombination, indexOfCard);
            //return true;
         }
         
      }
      else if (combinationType == Combination::type::RUN)
      {
         // Create a run from the cards and validate it 
         std::shared_ptr<Combination> run = std::shared_ptr<Combination>(new Run(cards));
         
         if (run->isValidCombination())
         {
            return std::make_tuple(true, indexOfCombination, indexOfCard);
            //return true;
         }
      }
      indexOfCombination++;
   }

   return std::make_tuple(false, -1, -1);
   //return false;
}

/* *********************************************************************
Function Name: removeCardFromCompleteCombination()
Purpose: Remove given card from the combination in completeCombination
   hash table
Parameters:
         Card card, the card we are removing from a combination
         int indexOfCombination, the index of the combination we are
            removing from
Return Value: none
Local Variables:
         string cardString, 
Algorithm:
         1) Get the stringified card
         2) Remove the card from the complete combination
         3) Remove the combination at indexOfCombination from the
            completeCombination (hash table) 
Assistance Received: none
********************************************************************* */
void CombinationFinder::removeCardFromCompleteCombination(Card card, int indexOfCombination)
{
   // The stringified card
   std::string cardString = card.toString();

   // Remove card from combination
   this->completeCombinations[cardString][indexOfCombination]->removeCard(card);

   // Remove combination from key
   this->completeCombinations[cardString].erase(this->completeCombinations[cardString].begin() + indexOfCombination);
}

/* *********************************************************************
Function Name: findIndexOfCard()
Purpose: Find the index the card exists in
Parameters:
         string card, the card we are checking for existance
         vector<Card> &cards, the cards to compare with card
Return Value: an int, the index of the card within cards, -1 if not found
Local Variables:
         string cardName, the string version of the card
Algorithm:
         1) Loop through the cards
         2) Get the string of the card
         3) If the string is equal to the one passed in, we found the card
         4) Return the index of the card, 
            -1 if we went through entire loop without finding it
Assistance Received: none
********************************************************************* */
int CombinationFinder::findIndexOfCard(std::string card, std::vector<Card> &cards)
{
   for (size_t i = 0; i < cards.size(); i++)
   {
      std::string cardName = cards[i].toString();

      // If the card is found
      if (card == cardName)
      {
         return i;
      }

   }
   return -1;
}

/* *********************************************************************
Function Name: removeCardFromVectorOfCards()
Purpose: Remove the card at index from vector of cards
Parameters:
         int index, the index of the vector we are removing
         vector<Card> &cards, a reference to the cards we are removing from
Return Value: none
Local Variables:
         none
Algorithm:
         1) Erase the card at index index
Assistance Received: none
********************************************************************* */
void CombinationFinder::removeCardFromVectorOfCards(int index, std::vector<Card> &cards)
{
   cards.erase(cards.begin() + index);
}

/* *********************************************************************
Function Name: getLargestRun()
Purpose: Get the largest run for the card in the table at [suit][number]
Parameters:
         int suit, the index of the suit in the table
         int number, the index of the number in the table
         vector<Card> &cards, a reference to an empty vector 
            passed in to hold the potential run
Return Value: none
Local Variables:
         Card card, card created at current index
Algorithm:
         1) Loop through the table's row at column suit
         2) If there's no card there, return
         3) Create card at current index
         4) Add to cards vector
Assistance Received: none
********************************************************************* */
void CombinationFinder::getLargestRun(int suit, int number, std::vector<Card> &cards)
{
   for (int i = number; i < this->NUMBERS; i++)
   {
      // If no card exists at location
      // Possible bug when determining partial runs (4S NULL 6S will be lost)
      if (this->table[suit][i] <= 0)
      {
         //std::cout << "no\n";
         return;
      }

      Card card = createCardFromTableIndex(suit, i);
      cards.push_back(card);
   }
}


/* *********************************************************************
Function Name: addCombinationToHashMap()
Purpose: Adds the found combination to the corresponding hash map 
   (complete or partial). Every card in the combination will have the
   value of all combinations it exists in i.e. if the combination is
   "3H 3D 3S" all of these cards will have at least the value "3H 3D 3S"
Parameters:
         shared_ptr<Combination> combination, the combination we're adding
         CombinationFinder::hashMapType combinationType, an enum denoting
            the type of combination we're adding
Return Value: none
Local Variables:
         vector<Card> cards, the cards in the combination passed in
         set<Card> uniqueCards, the unique cards in the combination
Algorithm:
         1) Erase the card at index index
Assistance Received: none
********************************************************************* */
void CombinationFinder::addCombinationToHashMap(std::shared_ptr<Combination> combination, hashMapType combinationType)
{
   // Get the cards from the combination
   std::vector<Card> cards = combination->getCardsInCombination();

   // Extract the unique cards from the combination
   std::set<Card> uniqueCards = { cards.begin(), cards.end() };

   if (combinationType == hashMapType::COMPLETE)
   {
      // Update each key's (card's) combinations
      for (Card card : uniqueCards)
      {
         completeCombinations[card.toString()].push_back(combination);
      }
   }
   else if (combinationType == hashMapType::PARTIAL)
   {
      // Update each key's (card's) combinations
      for (Card card : uniqueCards)
      {
         partialCombinations[card.toString()].push_back(combination);
      }
   }
}


/* *********************************************************************
Function Name: doesCardCompleteCombination()
Purpose: Check if adding a card to an incomplete combination completes 
   that combination (complete combinations only currently)
Parameters:
         Card card, the card we're checking if completes combination
         Combination::type combinationType, the type of combination
            to check against
Return Value: a bool, false if it's not a valid combination,
   true if it is a valid combination
Local Variables:
         shared_ptr<Combination> run, the Run object to check validity
         shared_ptr<Combination> book, the Book object to check validity
Algorithm:
         1) Add the card passed in to the vector of cards passed in
         2) Check the type of combination
         3) Create Run object if it's type::RUN
         4) Create Book object if it's type::BOOK
         5) Return false if it's neither
         5) Validate the object
         6) Return false if it's invalid
         7) Return true, it's a valid combination
Assistance Received: none
********************************************************************* */
bool CombinationFinder::doesCardCompleteCombination(Card card, std::vector<Card> combination, Combination::type combinationType)
{
   // Possible bug, 
   combination.push_back(card);

   if (combinationType == Combination::type::RUN)
   {
      // Create run from vector
      std::shared_ptr<Combination> run = std::shared_ptr<Combination>(new Run(combination));
      
      // Validate run
      if (!run->isValidCombination())
      {
         return false;
      }
   }
   else if (combinationType == Combination::type::BOOK)
   {
      // Create run from vector
      std::shared_ptr<Combination> book = std::shared_ptr<Combination>(new Book(combination));

      // Validate run
      if (!book->isValidCombination())
      {
         return false;
      }
   }
   else
   {
      return false;
   }

   // Valid combination
   return true;
}


/* *********************************************************************
Function Name: findRuns()
Purpose: Create all runs from the table
Parameters:
         none
Return Value: none
Local Variables:
         vector<Card> runCombination, vector to store the run
         int number, index of the number in the table
Algorithm:
         1) Loop through all the suits in the table
         2) Create a vector to store runCombination for each suit
         3) Loop through all numbers starting at 0
         4) Find the largest run starting at that index 
         5) If size is 3 or higher, make a Run object and remove those
            cards from the table
         6) If size is 2, make a PartialRun object and remove those cards
            from the table
         7) If size is less than 2, increment number index
         8) Clear the runCombination vector and try again
Assistance Received: none
********************************************************************* */
void CombinationFinder::findRuns()
{
   // Loop through each suit
   for (int suit = 0; suit < this->SUITS; suit++)
   {
      // To store the run
      std::vector<Card> runCombination;
      
      // Loop through each number and find largest run starting from that card (i.e. starting at 3S)
      int number = 0;
      while (number < this->NUMBERS)
      {
         getLargestRun(suit, number, runCombination);

         if (runCombination.size() >= 3)
         {
            makeCombination(runCombination, Combination::type::RUN);
         }
         // If it's a partial run (of size 2)
         else if (runCombination.size() == 2)
         {
            makePartialCombination(runCombination, Combination::type::PARTIAL_RUN);
         }
         else
         {
            number++;
         }
         runCombination.clear();
      }
   }
}

/* *********************************************************************
Function Name: findBooks()
Purpose: Create all books from the table
Parameters:
         none
Return Value: none
Local Variables:
         vector<Card> bookCombination, vector to store the book
         int amountOfCard, the number of cards at current index
         Card card, card at current index
         tuple<bool, int, int> removeCardResults, the results from
            removing the card at current index from a combination
            it exists in
         Card cardFromCombinationHashMap, the card we can remove from
            the Combination object inside the completeCombinations
            hash table
Algorithm:
         1) Loop through all numbers in the table
         2) Create vector bookCombination to store cards for potential
            book
         3) Loop through all suits in the table
         4) Get the amount of cards at current index
         5) Create a card object at current index
         6) Check if that card is being used for a combination
            (if it exists in a Combination object already)
         7) See if we can remove the card from the combination without
            invalidating it
         8) If we can remove it successfully, remove the card from 
            the combinations it exists in
         9) Add the card to bookCombination vector
         10) While there is a card at the current index,
         11) Add that card to bookCombination vector
         12) Subtract number of cards at index
         13) Check book sizes
         14) If size >= 3, make a Book
         15) If size == 2, make a PartialBook
Assistance Received: none
********************************************************************* */
void CombinationFinder::findBooks()
{
   // Loop through all cards number by number
   for (int number = 0; number < this->NUMBERS; number++)
   {
      std::vector<Card> bookCombination;
      for (int suit = 0; suit < this->SUITS; suit++)
      {
         int amountOfCard = this->table[suit][number];
         
         // Create create from current index
         Card card = createCardFromTableIndex(suit, number);

         // Check if a card is currently being used for a combination
         if (isCardInCombination(card))
         {
            // Retrieve whether or not we can remove it from the combination, the index of
            // the combination, and the index of the card
            std::tuple<bool, int, int> removeCardResults = canRemoveFromCombination(card);
            
            // If we can remove card from a combination
            if (std::get<0>(removeCardResults))
            {
               // The card we can remove
               Card cardFromCombinationHashMap = completeCombinations[card.toString()][std::get<1>(removeCardResults)]->at(std::get<2>(removeCardResults));
               
               // Potentially change this logic, we don't necessarily care if it completes the book, just
               // if we can safely use it. This only works if we have 2 cards in bookCombination and the
               // card at [suit][number] can be safely removed so this may skip over cards at certain suits
               if (doesCardCompleteCombination(cardFromCombinationHashMap, bookCombination, Combination::type::BOOK))
               {
                  //std::cout << card << "\n";
                  //std::cout << "we can remove " << card << "\n";

                  // Remove card from combination
                  removeCardFromCompleteCombination(card, std::get<1>(removeCardResults));

                  // Add to current book combination
                  bookCombination.push_back(card);
               }
               else
               {
                  //std::cout << card.toString() << " is used, but we can't use it!\n";
               }      
            }
         }

         // While there is at least 1 card in the table at current location
         // Push to combination
         while (amountOfCard >= 1)
         {
            //std::cout << card.toString();
            bookCombination.push_back(card);
            
            amountOfCard--;
         }

      }

      // If we find a book, add to complete combination hash table
      if (bookCombination.size() >= 3)
      {
         makeCombination(bookCombination, Combination::type::BOOK);         
      }
      // If it's a partial book, 
      else if (bookCombination.size() == 2)
      {
         makePartialCombination(bookCombination, Combination::type::PARTIAL_BOOK);
      }
   }
}

/* *********************************************************************
Function Name: makeCombination()
Purpose: Create Book or Run object from cards given the type
Parameters:
         vector<Card> combination, the cards for the combination
         Combination::type combinationType, the enum for type 
            of combination (type::BOOK or type::RUN)
Return Value: none
Local Variables:
         shared_ptr<Combination> book, the Book object
         shared_ptr<Combination> run, the Run object
Algorithm:
         1) Check type of combination
         2) If it's a book, create a Book object
         3) If it's a run, create a Run object
         4) Validate the object
         5) Add cards in object to completeCombinations hash table
            where their value is all of the cards
         6) Remove the count for each card from the table[][]
Assistance Received: none
********************************************************************* */
void CombinationFinder::makeCombination(std::vector<Card> combination, Combination::type combinationType)
{
   if (combinationType == Combination::type::BOOK)
   {
      std::shared_ptr<Combination> book = std::shared_ptr<Combination>(new Book(combination));

      // Verify the book is valid
      if (book->isValidCombination())
      {
         // Add cards in book combination to hash table
         addCombinationToHashMap(book, hashMapType::COMPLETE);

         // Remove count from table for each card
         subtractCardsFromTable(combination);
      }

      //std::cout << "book of " << book->at(0).getIntNumber() << "\n";
   }
   else if (combinationType == Combination::type::RUN)
   {
      std::shared_ptr<Combination> run = std::shared_ptr<Combination>(new Run(combination));

      // Verify the run is valid
      if (run->isValidCombination())
      {
         // Add cards in book combination to hash table
         addCombinationToHashMap(run, hashMapType::COMPLETE);

         // Remove count from table for each card
         subtractCardsFromTable(combination);
      }

      //std::cout << "run of " << run->at(0).getNumber() << run->at(0).getSuit() << "\n";
   }

   //printTable();
}


/* *********************************************************************
Function Name: makePartialCombination()
Purpose: Create partial book or partial run from cards given the type
Parameters:
         vector<Card> partialCombination, the cards for the 
            partial combination
         Combination::type partialCombinationType, the enum for type
            of combination (PARTIAL_BOOK or PARTIAL_RUN)
Return Value: none
Local Variables:
         shared_ptr<Combination> partialBook, the PartialBook object
         shared_ptr<Combination> partialRun, the PartialRun object
Algorithm:
         1) Check type of combination
         2) If it's a partial book, create a PartialBook object
         3) If it's a run, create a PartialRun object
         4) Validate the object
         5) Add cards in object to partialCombinations hash table
            where their value is all of the cards
         6) Remove the count for each card from the table[][]
Assistance Received: none
********************************************************************* */
void CombinationFinder::makePartialCombination(std::vector<Card> partialCombination, Combination::type partialCombinationType)
{
   if (partialCombinationType == Combination::type::PARTIAL_BOOK)
   {
      std::shared_ptr<Combination> partialBook = std::shared_ptr<Combination>(new PartialBook(partialCombination));

      // Verify the partial book is valid
      if (partialBook->isValidCombination())
      {
         // Add cards in book combination to hash table
         addCombinationToHashMap(partialBook, hashMapType::PARTIAL);

         // Remove count from table for each card
         subtractCardsFromTable(partialCombination);
      }

      //std::cout << "partial book of " << partialBook->at(0).getIntNumber() << "\n";
   }
   else if (partialCombinationType == Combination::type::PARTIAL_RUN)
   {
      std::shared_ptr<Combination> partialRun = std::shared_ptr<Combination>(new PartialRun(partialCombination));

      // Verify the partial run is valid
      if (partialRun->isValidCombination())
      {
         // Add cards in book combination to hash table
         addCombinationToHashMap(partialRun, hashMapType::PARTIAL);

         // Remove count from table for each card
         subtractCardsFromTable(partialCombination);

         //std::cout << "partial run of " << partialRun->at(0).getIntNumber() << partialRun->at(0).getSuit() << "\n";
      }

   }
   
   //printTable();
}


/* *********************************************************************
Function Name: extractBooksAndRunsFromHashMap()
Purpose: Extract the books and runs (as vectors) from the complete hash map
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through all the keys in the completeCombinations
            hash table
         2) Check the state of each combination in the key's values
         3) Check the type of combination if it has not yet been extracted
         4) Push to the respected vector of combination (book/run)
         5) Set Combination's extracted boolean value to have been extracted
Assistance Received: none
********************************************************************* */
void CombinationFinder::extractBooksAndRunsFromHashMap()
{
   // For each key in complete combinations
   for (auto key : completeCombinations)
   {
      auto value = key.second;

      for (auto combo : value)
      {
         // If the combination has not been extracted
         if (!combo->isExtracted())
         {
            // Check the combination type

            // If it's a book, push to book vector
            if (combo->getType() == Combination::type::BOOK)
            {
               this->books.push_back(combo->getCardsInCombination());
            }
            // If it's a run, push to run vector
            else if (combo->getType() == Combination::type::RUN)
            {
               this->runs.push_back(combo->getCardsInCombination());
            }

            // Set combination to be extracted
            combo->setExtracted();
         }
      }
   }
}


/* *********************************************************************
Function Name: createCombinationsFromPartialCombinations()
Purpose: Create combinations from partial combinations using wild cards
   which are stored in the vector member variable wildCards.
Parameters:
         none
Return Value: none
Local Variables:
         vector<shared_ptr<Combination>> values, the combinations
            in the partialCombinations hash table from a given key
         vector<Card> newCombination, the cards for the new 
            complete combination we are creating
         vector<Card> partialCombo, the cards in the PartialCombination
            object
Algorithm:
         1) Loop through all the keys in the partialCombinations 
            hash table
         2) Loop through all of the combinations in each key
         2) Check the state of each combination in the key's values
         3) Check the type of combination if it has not yet been extracted
         4) If it hasn't been, check if we have at least 1 wild card
         5) If we have at least 1 wild card, use it to complete the
            partial combination
         6) Remove the wild card from member variable wildCards
         7) Check the type of combination the partial combination 
         8) If the type is type::PARTIAL_BOOK, push vector to books
         9) If the type is type::PARTIAL_RUN, push vector to runs
         10) Set partial combination to have been extracted once we
            add to member variable books/runs
Assistance Received: none
********************************************************************* */
void CombinationFinder::createCombinationsFromPartialCombinations()
{
   // For each key in partial combinations
   for (auto key : partialCombinations)
   {
      auto values = key.second;
      
      // For each combination that key has
      for (auto combo : values)
      {
         // If the combination has not been extracted
         if (!combo->isExtracted())
         {
            // If there is at least 1 wild card
            if (!this->wildCards.empty())
            {
               std::vector<Card> newCombination = combo->getCardsInCombination();
               newCombination.push_back(this->wildCards.front());

               this->wildCards.erase(this->wildCards.begin());

               // Check the combination type

               // If it's a book, push to book vector
               if (combo->getType() == Combination::type::PARTIAL_BOOK)
               {
                  this->books.push_back(newCombination);
               }
               // If it's a run, push to run vector
               else if (combo->getType() == Combination::type::PARTIAL_RUN)
               {
                  this->runs.push_back(newCombination);
               }

               combo->setExtracted();
            }
            else
            {
               combo->setExtracted();

               // Insert cards in partial combination to partial card vector
               std::vector<Card> partialCombo = combo->getCardsInCombination();
               this->partialCards.insert(partialCards.end(), partialCombo.begin(), partialCombo.end());
            }
         }
      }

   }
}

/* *********************************************************************
Function Name: addWildCardsCompleteCombinations()
Purpose: Use wild cards to complete/make combinations. We would use this
   function if wild cards can't be used on partial combinations
   (there are none left)
Parameters:
         Combination::type combinationType, the type of combination to
            complete
Return Value: none
Local Variables:
         none      
Algorithm:
         1) Check the type of combination
         2) While there are wild cards left
         3) Push the next wild card to the end of the first combination
         4) Erase the wild card
Assistance Received: none
********************************************************************* */
void CombinationFinder::addWildCardsCompleteCombinations(Combination::type combinationType)
{

   if (this->singleCards.size() == 1)
   {
      //std::cout << "we messed up\n";
   }

   // If it's a book, add to book
   if (combinationType == Combination::type::BOOK)
   {
      while (!this->wildCards.empty())
      {
         this->books[0].push_back(this->wildCards.front());
         this->wildCards.erase(this->wildCards.begin());
      }
   }
   // If it's a run, add to run
   else if (combinationType == Combination::type::RUN)
   {
      while (!this->wildCards.empty())
      {
         this->runs[0].push_back(this->wildCards.front());
         this->wildCards.erase(this->wildCards.begin());
      }
   }
   
}

/* *********************************************************************
Function Name: extractRemainingCardsFromTable()
Purpose: Loop through table of non-wild cards and adds them to
   member variable singleCards vector
Parameters:
         none
Return Value: none
Local Variables:
         Card card, the card we're extracting from table
Algorithm:
         1) Loop through all cards number by number
         2) Loop through all cards suit by suit
         3) While there is at least 1 card in the table at current index
         4) Create card at current index
         5) Push card to member variable singleCards vector
         6) Remove card from table
Assistance Received: none
********************************************************************* */
void CombinationFinder::extractRemainingCardsFromTable()
{
   // Loop through all cards number by number
   for (int number = 0; number < this->NUMBERS; number++)
   {
      // Loop through all cards suit by suit
      for (int suit = 0; suit < this->SUITS; suit++)
      {
         // While there are cards at current index
         while (this->table[suit][number] >= 1)
         {
            // Create card and push to single cards
            Card card = createCardFromTableIndex(suit, number);
            this->singleCards.push_back(card);
            
            // Remove from table
            this->table[suit][number]--;
         }
      }
   }
}

/* *********************************************************************
Function Name: createCombinationsFromSingleCards()
Purpose: Create combinations from single cards remaining that haven't
   been used for combinations
Parameters:
         none
Return Value: none
Local Variables:
         vector<Card> singlesToDelete, the single cards we must remove
            from the table after they are used to create combinations
         vector<Card> combination, combination we are making from using
            single cards along with wild cards
         int index, index of card to delete from member variable
            vector singleCards
Algorithm:
         1) Declare empty vector to store single cards used for
            combinations
         2) Loop through all cards in member variable vector singleCards
         3) If we have at least 2 wild cards
         4) Make combination using a single card and 2 wild cards
         5) Add combination to member variable book vector
         6) Add the single card to singlesToDelete
         7) Loop through singlesToDelete
         8) Find the index it exists in member variable vector singleCards
         9) Delete card from singleCards
Assistance Received: none
********************************************************************* */
void CombinationFinder::createCombinationsFromSingleCards()
{
   // The single cards used to make complete combinations
   // We need to remove these
   std::vector<Card> singlesToDelete;

   // For each single card, check if we have 2 wild cards we can use to complete a combination
   for (Card singleCard : this->singleCards)
   {
      // Potential bug if we have 3 wild cards and 1 single card left after initial combinations
      // using non-wild cards
      if (this->wildCards.size() >= 2)
      {
         std::vector<Card> combination;
         combination.push_back(singleCard);

         // Add two wild cards to combination and delete from wild card vector
         for (int i = 0; i < 2; i++)
         {
            combination.push_back(this->wildCards.front());
            this->wildCards.erase(this->wildCards.begin());
         }

         // Add to book vector (it doesn't matter which we choose, it's a book OR a run)
         this->books.push_back(combination);

         //this->singleCards.erase(singleCard);
         singlesToDelete.push_back(singleCard);
      }

   }

   // Remove all single cards that were used to make combinations
   for (Card singleCard : singlesToDelete)
   {
      // Find the index of the card to remove
      int index = findIndexOfCard(singleCard.toString(), singlesToDelete);

      // Remove from single cards vector
      this->singleCards.erase(this->singleCards.begin() + index);
   }
   
}

/* *********************************************************************
Function Name: getScore()
Purpose: Get score of cards left over
Parameters:
         none
Return Value: an int, the score of the remaining cards
Local Variables:
         int score, the total value of the remaining cards
Algorithm:
         1) Initialize score to be 0
         2) Loop through remaining cards
         3) Add each card's value to score
         4) Return the score
Assistance Received: none
********************************************************************* */
int CombinationFinder::getScore()
{
   int score = 0;

   // Add value of each remaining card to score
   for (Card remainingCard : this->remainingCards)
   {
      score += remainingCard.getValue();
   }

   return score;
}


/* *********************************************************************
Function Name: combineRemainingCards()
Purpose: Combine the remaining cards not used in books or runs. This
   includes partial combinations not used, single cards left in table, and
   remaining wild cards not used
Parameters:
         none
Return Value: none
Local Variables:
         vector<Card> remaining, the remaining cards not used
Algorithm:
         1) Declare empty vector<Card> remaining
         2) Add the single cards to remaining
         3) Add the partial cards to remaining
         4) Add the wild card to remaining
         5) Set member variable remainingCards to remaining
Assistance Received: none
********************************************************************* */
void CombinationFinder::combineRemainingCards()
{
   std::vector<Card> remaining;
   remaining.insert(remaining.end(), singleCards.begin(), singleCards.end());
   remaining.insert(remaining.end(), partialCards.begin(), partialCards.end());
   remaining.insert(remaining.end(), wildCards.begin(), wildCards.end());
   
   this->remainingCards = remaining;
}

/* *********************************************************************
Function Name: getNumberOfRemainingCards()
Purpose: Get the number of remaining cards from making combinations 
   (need to make combinations first)
Parameters:
         none
Return Value: a const int, the number of remaining cards
Local Variables:
         none
Algorithm:
         1) Return the number of remaining cards
Assistance Received: none
********************************************************************* */
int CombinationFinder::getNumberOfRemainingCards() const
{
   return this->remainingCards.size();
}

/* *********************************************************************
Function Name: getNumberOfSingleCards()
Purpose: Get the number of single cards from making combinations
Parameters:
         none
Return Value: a const int, the number of single cards
Local Variables:
         none
Algorithm:
         1) Return the number of single cards
Assistance Received: none
********************************************************************* */
int CombinationFinder::getNumberOfSingleCards() const
{
   return this->singleCards.size();
}

/* *********************************************************************
Function Name: getBooks()
Purpose: Return a copy of the member variable vector of books 
Parameters:
         none
Return Value: a const vector<vector<Card>>, the vector of books made
Local Variables:
         none
Algorithm:
         1) Return the member variable books
Assistance Received: none
********************************************************************* */
std::vector<std::vector<Card>> CombinationFinder::getBooks() const
{
   return this->books;
}

/* *********************************************************************
Function Name: getRuns()
Purpose: Return a copy of the member variable vector of runs
Parameters:
         none
Return Value: a const vector<vector<Card>>, the vector of runs made
Local Variables:
         none
Algorithm:
         1) Return the member variable runs
Assistance Received: none
********************************************************************* */
std::vector<std::vector<Card>> CombinationFinder::getRuns() const
{
   return this->runs;
}

/* *********************************************************************
Function Name: retrieveRemainingCards()
Purpose: Return the cards remaining from making combinations
Parameters:
         none
Return Value: a const vector<vector<Card>>, the vector of runs made
Local Variables:
         none
Algorithm:
         1) Return the member variable runs
Assistance Received: none
********************************************************************* */
// Return the cards remaining from making combinations
std::vector<Card> CombinationFinder::retrieveRemainingCards() const
{
   return this->remainingCards;
}

/* *********************************************************************
Function Name: findWorstCard()
Purpose: Find the least valuable card in the hand
Parameters:
         none
Return Value: a string, denoting the worst card
Local Variables:
         none
Algorithm:
         1) Check if we have any single cards
         2) Remove highest value single card if so
         3) If not, check if we have any partial cards
         4) Remove highest value partial card if so
         5) If not, find highest value card in combinations
         such that removing it does not invalidate the combination
         6) Return the card we found
Assistance Received: none
********************************************************************* */
std::pair<std::string, std::string> CombinationFinder::findWorstCard()
{
   int index = 0;
   std::string worstCard = "";
   std::string reason = "";
   
   try
   {
      // If there are single cards remaining
      if (this->singleCards.size() > 0)
      {
         // Get highest value single card
         index = indexOfHighestValueCard(this->singleCards);
         worstCard = this->singleCards[index].toString();

         reason = "it was the highest value single card";
      }
      // If there are partial cards remaining
      else if (this->partialCards.size() > 0)
      {
         try
         {
            this->partialCards = Combination::sortCards(this->partialCards);
            index = indexOfHighestValueCard(this->partialCards);
            //index = 0;
            worstCard = this->partialCards[index].toString();

            reason = "it was the highest value partial combination card";
         }
         catch (const std::out_of_range& oor)
         {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
         }

      }
      // If we have complete combination
      else if (this->books.size() > 0)
      {
         for (auto book : books)
         {
            // If we can afford to remove a card from book
            if (book.size() > 3)
            {
               int choice = rand() % 2;
               if (choice == 1)
               {
                  // Take last card
                  index = book.size() - 1;
               }
               else
               {
                  // Take first card
                  index = 0;
               }
               
               worstCard = book[index].toString();

               reason = "it was the highest value card of a combination where it wasn't needed";
            }
            // If we need to remove a card from a book
            else if (book.size() > 1)
            {
               // Take last card
               index = book.size() - 1;
               worstCard = book[index].toString();

               reason = "unfortunately we had no choice but to destroy a book";
            }
         }
      }
      else if (this->runs.size() > 0)
      {
         for (auto run : runs)
         {
            // If we can afford to remove a card from book
            if (run.size() > 3)
            {
               int choice = rand() % 2;
               if (choice == 1)
               {
                  // Take last card
                  index = run.size() - 1;
               }
               else
               {
                  // Take first card
                  index = 0;
               }
               worstCard = run[index].toString();

               reason = "it was the highest value card of a combination where it wasn't needed";
            }
            // If we need to remove a card from a run
            else if (run.size() > 1) 
            {
               // Take last card
               index = run.size() - 1;
               worstCard = run[index].toString();

               reason = "unfortunately we had no choice but to destroy a run";
            }
         }
      }

   }
   catch (const std::out_of_range& oor)
   {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
   }

   std::pair<std::string, std::string> worstCardAndReason(worstCard, reason);

   return worstCardAndReason;
}

/* *********************************************************************
Function Name: indexOfHighestValueCard()
Purpose: Return the index of the highest value card in a vector of cards
Parameters:
         vector<Card> cards, the to find the highest value of
Return Value: an int, the index of the highest value card in the vector
Local Variables:
         int value, the value of the card
         int index, the index of the card
Algorithm:
         1) Sort the cards
         2) Loop through the card
         3) Get the value and compare to previous value
         4) If value of card at current index is higher than value 
         5) Set value to be value of card
         6) Increment index
         7) Return the index after loop
Assistance Received: none
********************************************************************* */
// Return the index of the highest value card in a vector of cards
// Returns 0 if there is at least 1 card when they are all the same value
int CombinationFinder::indexOfHighestValueCard(std::vector<Card> cards)
{
   cards = Combination::sortCards(cards);
   int value = INT_MIN;
   int index = 0;

   for (size_t i = 0; i < cards.size(); i++)
   {
      if (cards[i].getValue() > value)
      {
         value = cards[i].getValue();
         index = i;
      }

   }

   return index;
}

// Bandaid for wild cards that aren't accounted for 
// Return remaining wild cards
std::vector<Card> CombinationFinder::getRemainingWilds() const
{
   return this->wildCards;
}