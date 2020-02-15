#include "computer.h"

/* *********************************************************************
Function Name: chooseGameOption()
Purpose: Get the option the computer chooses for the game option
The value can be 1 for saving the game, 2 for making a move, or
3 for quitting the game.
Parameters:
         none
Return Value: a int, the choice the computer made
Local Variables:
         none
Algorithm:
         1) Always returns 2 to make a move, all other moves
         don't make sense in the context of winning
Assistance Received: none
********************************************************************* */
int Computer::chooseGameOption()
{
   printMenu();
   
   std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
   std::cout << "The computer chose to make a move because it wants to win\n";
   std::cout << "--------------------------------------------------------------------------------------------------------------------\n";

   return static_cast<int>(Player::gameOption::MAKE_MOVE);
}

/* *********************************************************************
Function Name: move()
Purpose: Get the move the computer will make. Will either be draw from
draw pile or draw from discard pile
Parameters:
         none
Return Value: a int, the choice the computer made
Local Variables:
         none
Algorithm:
         1) Check if the card at the top of the discard pile leaves
         you with less than or equal remaining cards from making
         combinations, than your current hand
         2) If it doesn't, draw from draw pile
Assistance Received: none
********************************************************************* */
int Computer::move()
{
   CombinationFinder::Order order = bestOrder(this->hand);
   CombinationFinder comboFinder(this->hand);
   comboFinder.findCombinations(order);

   if (shouldDrawFromDiscard())
   {
      std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
      std::cout << "The computer chose to draw from the discard pile because\nthe discard card did not increase the number single cards in the hand\n";
      std::cout << "--------------------------------------------------------------------------------------------------------------------\n\n";

      return static_cast<int>(Player::moveOption::DRAW_DISCARD);
   }
   else
   {
      std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
      std::cout << "The computer chose to draw from the drawing pile because\nthe discard card increased the number single cards in the hand\n";
      std::cout << "--------------------------------------------------------------------------------------------------------------------\n\n";

      return static_cast<int>(Player::moveOption::DRAW_DECK);
   }

}

/* *********************************************************************
Function Name: help()
Purpose: Find out what move the Human should make
Parameters:
         vector<Card> hand, the cards in the hand
         Card discardCard, the card at the top of discard pile,
         Computer::Help helpType, an enum denoting the type of help
Return Value: none
Local Variables:
         a Computer object, used to call the Computer's function
         using the hand and discard card passed in
Algorithm:
         1) Check if computer was asked for help in drawing a card
         2) If yes, create a Computer object to find out the best order to make
         books and runs in
         3) 
         4) Print its suggestion
Assistance Received: none
********************************************************************* */
void Computer::help(std::vector<Card> hand, Card discardCard, Computer::Help helpType)
{
   if (helpType == Computer::Help::DRAW_HELP)
   {
      // Temporary computer object to set its hand and discard card to the ones passed in
      // so we can call Player and Computer methods
      Computer tempComputer;

      // Initialize object to have player's cards
      tempComputer.setHand(hand);
      tempComputer.setTopOfDiscard(discardCard);

      // Find the best order to make combinations in
      CombinationFinder::Order order = tempComputer.bestOrder(tempComputer.hand);
      CombinationFinder comboFinder(tempComputer.hand);
      comboFinder.findCombinations(order);

      // Check if we should draw from the discard pile or not
      if (tempComputer.shouldDrawFromDiscard())
      {
         std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
         std::cout << "The computer suggests you chose to draw from the discard pile because\nthe discard card did not increase the number single cards in the hand\n";
         std::cout << "--------------------------------------------------------------------------------------------------------------------\n";

      }
      else
      {
         std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
         std::cout << "The computer suggests you to draw from the drawing pile because\nthe discard card increased the number single cards in the hand\n";
         std::cout << "--------------------------------------------------------------------------------------------------------------------\n\n";

      }

   }
   else if (helpType == Computer::Help::DISCARD_HELP)
   {
      Computer tempComputer;

      // Initialize object to have player's cards
      tempComputer.setHand(hand);
      tempComputer.setTopOfDiscard(discardCard);

      // Find the best order to make combinations in
      CombinationFinder::Order order = tempComputer.bestOrder(tempComputer.hand);
      CombinationFinder finder(tempComputer.hand);
      finder.findCombinations(order);

      // Find the worst card in the hand
      std::pair<std::string, std::string> worstCardandReason = finder.findWorstCard();
      std::string card = worstCardandReason.first;
      std::string reason = worstCardandReason.second;

      std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
      std::cout << "The computer suggests you remove " << card << " from its hand\nbecause " << reason << "\n";
      std::cout << "--------------------------------------------------------------------------------------------------------------------\n\n";
   }   
}

/* *********************************************************************
Function Name: printMenu()
Purpose: Print the menu of game options the computer can take
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Check if the card at the top of the discard pile makes
         a book or run. If so, draw from discard pile
         2) If it doesn't, draw from draw pile
Assistance Received: none
********************************************************************* */
void Computer::printMenu()
{
   std::cout <<
      "1. Save the game\n" <<
      "2. Make a move\n" <<
      "3. Quit the game\n";
}


/* *********************************************************************
Function Name: getCardToDiscard()
Purpose: Get the card the computer thing it should get rid of
Parameters:
         none
Return Value: a string, denoting the card to discard
Local Variables:
         none
Algorithm:
         1) Create a CombinationFinder object
         2) Find all combinations
         3) Find the worst card of the remaining ones
         4) Return that card
Assistance Received: none
********************************************************************* */
// TODO: possibly change so that it does not remove wild cards if they are single cards
std::pair<bool, std::string> Computer::getCardToDiscard()
{
   CombinationFinder::Order order = bestOrder(this->hand);
   CombinationFinder finder(this->hand);
   finder.findCombinations(order);

   std::pair<std::string, std::string> worstCardandReason = finder.findWorstCard();
   std::string card = worstCardandReason.first;
   std::string reason = worstCardandReason.second;

   std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
   std::cout << "The computer removed " << card << " from its hand because " << reason << "\n";
   std::cout << "--------------------------------------------------------------------------------------------------------------------\n\n";

   std::pair<bool, std::string> cardAndHelp{ false, card };

   return cardAndHelp;

}

/* *********************************************************************
Function Name: toString()
Purpose: Print the string equivalent of the type of Player
Parameters:
         none
Return Value: a const string, denoting the Player type
Local Variables:
         none
Algorithm:
         1) Return the string "Computer"
Assistance Received: none
********************************************************************* */
std::string Computer::toString() const
{
   return "Computer";
}

/* *********************************************************************
Function Name: shouldDrawFromDiscard()
Purpose: Check if we should draw from the discard pile or drawing pile
Parameters:
         none
Return Value: a bool, denoting whether or not we should pick from the
the discard pile
Local Variables:
         CombinationFinder::Order enum, the order we should
Algorithm:
         1) Get best order to make combinations in given current hand
         2) Get best order to make combinations in given current hand
            plus the top of the discard pile
         3) Compare the number of single cards remaining from making all
            combinations in both sets of cards
         4) If we end up with the same amount of remaining cards or less, we should draw
            from the discard pile, return true
         5) If we end up with more remaining cards, we are working backwards and should
            not draw from the discard pile, return false
Assistance Received: none
********************************************************************* */
bool Computer::shouldDrawFromDiscard()
{
   // Get best order of combinations with current hand
   CombinationFinder::Order order = bestOrder(this->hand);

   // Get number of remaining cards with current hand
   int currentSingleCards = numberOfSingleCards(this->hand, order);

   // TEMP USE FOR CHECKING BUG
   int remainingCards = numberOfRemainingCards(this->hand, order);
   
   // Get number of remaining cards with current hand + card on top of discard
   std::vector<Card> handWithDiscard;
   handWithDiscard.push_back(this->topOfDiscard);
   handWithDiscard.insert(handWithDiscard.end(), this->hand.begin(), this->hand.end());

   // Get best order of combinations with hand plus discard card
   CombinationFinder::Order discardOrder = bestOrder(handWithDiscard);
   
   // TEMP USE FOR CHECKING BUG
   int remainingCardsWithDiscard = numberOfRemainingCards(handWithDiscard, discardOrder);

   int singleCardsWithDiscard = numberOfSingleCards(handWithDiscard, discardOrder);

   // If we end up with the same amount of remaining cards or less, we should draw
   // from the discard pile
   if (currentSingleCards >= singleCardsWithDiscard)
   {
      return true;
   }

   //TEMP FOR DEBUGGING
   /*if (remainingCards >= remainingCardsWithDiscard)
   {
      return true;
   }*/
   //TEMP FOR DEBUGGING

   // If we end up with more remaining cards, we are working backwards and should
   // not draw from the discard pile
   return false;
}

/* *********************************************************************
Function Name: numberOfRemainingCards()
Purpose: Return the number of remaining cards after making combinations 
   from the cards in the hand
Parameters:
         vector<Card> hand, the cards in the Player's hand
         CombinationFinder::Order combinationOrder, an enum denoting
            which order to find combinations in

Return Value: an int, denoting the number of cards remaining after
   combinations are made
Local Variables:
         CombinationFinder handFinder, CombinationFinder object that
            takes the Player's cards and attempts to find the 
            best combination
Algorithm:
         1) Find the number of remaining cards after making combinations
         2) Return the number of remaining cards
Assistance Received: none
********************************************************************* */
int Computer::numberOfRemainingCards(std::vector<Card> hand, CombinationFinder::Order combinationOrder)
{
   // Make combinations using the cards and the order passed in
   CombinationFinder handFinder(hand);
   handFinder.findCombinations(combinationOrder);
   
   // Return number of cards left after making combinations
   return handFinder.getNumberOfRemainingCards();
}

/* *********************************************************************
Function Name: numberOfSingleCards()
Purpose: Return the number of single cards after making combinations
   from vector of cards
Parameters:
         vector<Card> hand, the cards in the Player's hand
         CombinationFinder::Order combinationOrder, an enum denoting
            which order to find combinations in
Return Value: an int, denoting the number of single cards 
Local Variables:
         CombinationFinder handFinder, CombinationFinder object that
            takes the Player's cards and attempts to find the
            best combination
Algorithm:
         1) Find the number of remaining cards after making combinations
         2) Return the number of remaining cards
Assistance Received: none
********************************************************************* */
// Return the number of single cards after making combinations from vector of cards
int Computer::numberOfSingleCards(std::vector<Card> hand, CombinationFinder::Order combinationOrder)
{
   CombinationFinder handFinder(hand);
   handFinder.findCombinations(combinationOrder);

   // Return number of cards left after making combinations
   return handFinder.getNumberOfSingleCards();
}