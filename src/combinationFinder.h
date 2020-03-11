#ifndef COMBINATIONFINDER_H
#define COMBINATIONFINDER_H

#include "book.h"
#include "run.h"
#include "partialBook.h"
#include "partialRun.h"
#include <unordered_map>   // for storing combinations
#include <set>             // for retrieving unique cards from a combination
#include <memory>	   // smart pointers
#include <limits.h>	   // INT_MAX INT_MIN

class CombinationFinder
{
   public:
      CombinationFinder() = default;
      ~CombinationFinder() = default;

      // Overloaded constructor
      CombinationFinder(std::vector<Card> cards);

      // Specifies which combinations we will make first
      enum class Order {
         UNDEFINED = 0,
         BOOKS_FIRST,
         RUNS_FIRST
      };

      // Get the number of remaining cards from making combinations
      int getNumberOfRemainingCards() const;

      // Get the number of single cards from making combinations
      int getNumberOfSingleCards() const;

      // Get the books
      std::vector<std::vector<Card>> getBooks() const;

      // Get the runs
      std::vector<std::vector<Card>> getRuns() const;

      // Return the cards remaining from making combinations
      std::vector<Card> retrieveRemainingCards() const;

      // Find all combinations
      void findCombinations(Order combinationOrder);

      // Get score of cards
      int getScore();

      // Find the least valuable card in the hand
      std::pair<std::string, std::string> findWorstCard();

      // Combine the remaining cards not used in books or runs
      // This includes partial combinations not used, single cards left in table, and
      // remaining wild cards not used
      void combineRemainingCards();

      // Bandaid for wild cards that aren't accounted for 
      // Return remaining wild cards
      std::vector<Card> getRemainingWilds() const;

   private:
      // Number of suits and numbers
      int const SUITS = 5;
      int const NUMBERS = 11;

      // The table to store the amount of each cards remaining in the hand
      int table[5][11] = { 0 };

      // Enum to distinguish type of hash map
      enum class hashMapType {
         UNDEFINED = 0,
         COMPLETE,
         PARTIAL
      };

      // Original cards passed in
      std::vector<Card> cards;

      // Wild cards and jokers
      std::vector<Card> wildCards;

      // Books and runs make from cards passed into constructor
      std::vector<std::vector<Card>> books;
      std::vector<std::vector<Card>> runs;

      // Non-wild cards that haven't been used for combinations or partial combinations
      std::vector<Card> singleCards;

      // Non-wild cards in partial combinations that can't be used
      std::vector<Card> partialCards;

      // Cards that haven't been used for anything and can't be used for any combination
      // even with wild cards
      std::vector<Card> remainingCards;

      // Stores which cards hold a complete combination
      std::unordered_map <std::string, std::vector<std::shared_ptr<Combination>>> completeCombinations;

      // Stores which cards hold a partial combination
      std::unordered_map <std::string, std::vector<std::shared_ptr<Combination>>> partialCombinations;

      // The corresponding table index of each suit
      std::map<std::string, int> indexOfSuit;

      // The corresponding table index of each number
      std::map<std::string, int> indexOfNumber;

      // The corresponding suit string for the index of table (i.e. "D")
      std::map<int, std::string> suitOfIndex;

      // The corresponding number string for the index of table (i.e. "5")
      std::map<int, std::string> numberOfIndex;

      // The corresponding value of each number for a card
      std::map<std::string, int> valueOfCard;

      // Initialize maps that map indices to strings
      void initializeMaps();

      // Add card to the table
      // Increments the index in the table of the cards's suit and number
      inline void addCardToTable(Card card);

      // Remove wild cards and jokers from the cards and push to separate vector
      void separateWildCards();

      // Populate the table with non-wild cards
      void populateTheTable();

      // Create a card object from the current point in the table
      Card createCardFromTableIndex(int suitIndex, int numberIndex);

      // Remove the given cards from the table
      // In other words, subtract the amount of cards existing in the table 
      // since they were used for a combination of any type
      void subtractCardsFromTable(std::vector<Card> combination);

      // Check if a card is currently being used for a combination
      bool isCardInCombination(Card card);

      // Check if removing a card invalidates a combination
      // Returns a tuple contain a bool of whether or not it invalidates the combination,
      // an integer representing the index of the combination,
      // and an integer representing the index of the card in the combination
      // Returns false, -1, -1 if it invalidates a combination
      std::tuple<bool, int, int> canRemoveFromCombination(Card card);

      // Remove given card from the combination in complete hash table
      void removeCardFromCompleteCombination(Card card, int indexOfCombination);

      // Find the index the card exists in
      int findIndexOfCard(std::string card, std::vector<Card> &cards);

      // Remove the card at index from vector of cards
      void removeCardFromVectorOfCards(int index, std::vector<Card> &cards);

      // Get the largest run for the card in the table at [suit][number]
      void getLargestRun(int suit, int number, std::vector<Card> &cards);

      // Adds the found combination to the hash map
      // Every card in the combination will have the value of all combinations it exists in
      // i.e. if the combination is "3H 3D 3S" all of these cards will have at least the value "3H 3D 3S"
      void addCombinationToHashMap(std::shared_ptr<Combination> combination, hashMapType combinationType);

      // Check if adding a card to an incomplete combination completes that combination
      bool doesCardCompleteCombination(Card card, std::vector<Card> combination, Combination::type combinationType);

      // Create all runs from the table
      void findRuns();

      // Create all books from the table
      void findBooks();

      // Create book or run from cards given the type
      void makeCombination(std::vector<Card> combination, Combination::type combinationType);

      // Create partial book or partial run from cards given the type
      void makePartialCombination(std::vector<Card> partialCombination, Combination::type combinationType);

      // Extract the books and runs from the complete hash map
      // This will loop through all the keys in the hash map,
      // check the state of each combination in the key's values,
      // check the type of combination if it has not yet been extracted,
      // and the push to the respected vector of combination (book/run)
      void extractBooksAndRunsFromHashMap();

      // Create combinations from partial combinations using wild cards which are
      // stored in the vector named wildCards.
      // If there are no partial combinations, we will use them on combinations
      // if there are no combinations, we will make combinations of only wild cards
      void createCombinationsFromPartialCombinations();

      // Loops through table of non-wild cards and adds them to singleCards vector
      void extractRemainingCardsFromTable();

      // Create combinations from single cards remaining that haven't been used for books/runs
      void createCombinationsFromSingleCards();

      // Add wild cards to complete combination
      // We would use this function if wild cards can't be used on partial combinations (there are none left)
      void addWildCardsCompleteCombinations(Combination::type combinationType);

      // Return the index of the highest value card in a vector of cards
      // Returns 0 if there is at least 1 card when they are all the same value
      int indexOfHighestValueCard(std::vector<Card> cards);

      // Print current state of the table
      void printTable();
};

#endif
