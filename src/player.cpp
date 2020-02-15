#include "player.h"

/* *********************************************************************
Function Name: serialize()
Purpose: Return serialzied Player object containging the name, 
   player score, and player hand for use with serialization
Parameters:
         vector<Card> cards, the Card objects in the PartialBook
Return Value: a const string, the serialized Player object
Local Variables:
         none
Algorithm:
         1) Create a string to store the serialized Player object
         2) Add the type to the string
         3) Add the score to the string
         4) Add each card to the string
         5) Return the string; the serialized Player
Assistance Received: none
********************************************************************* */
std::string Player::serialize() const
{
   std::string playerString;

   // Add the player type to the player string
   playerString += this->toString();
   playerString += ":\n";
   
   // Add the score to the player string
   playerString += "   Score: " + std::to_string(score) + "\n";
   
   // Add each card in the hand to the player string
   playerString += "   Hand: ";
   for (Card card : hand)
   {
      playerString += card.toString() + " ";
   }

   return playerString;
}

/* *********************************************************************
Function Name: setHand()
Purpose: To add a specified card to the player's hand
Parameters:
         None
Local Variables: None
Algorithm:
         1) Push the card passed in to the player's hand
Assistance Received: none
********************************************************************* */
void Player::setHand(std::vector<Card> cards)
{
   this->hand = cards;
}

/* *********************************************************************
Function Name: addToHand()
Purpose: To add a specified card to the player's hand
Parameters:
         None
Local Variables: None
Algorithm:
         1) Push the card passed in to the player's hand
Assistance Received: none
********************************************************************* */
void Player::addToHand(Card card)
{
   this->hand.push_back(card);
}

/* *********************************************************************
Function Name: clearHand()
Purpose: Clear the player's hand
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Clear the hand
Assistance Received: none
********************************************************************* */
void Player::clearHand()
{
   this->hand.clear();
}

/* *********************************************************************
Function Name: resetDiscardCard()
Purpose: Sets player's discard card to a blank card
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Create an Card using default constructor. Since its toString()
            will return "", we can tell if there's a discard card
         2) Set the player's discard card to the blank card
Assistance Received: none
********************************************************************* */
void Player::resetDiscardCard()
{
   Card blankCard;
   this->topOfDiscard = blankCard;
}

/* *********************************************************************
Function Name: printHand()
Purpose: Print cards in hand
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through each card in the hand
         2) Print the card at each index
Assistance Received: none
********************************************************************* */
void Player::printHand()
{
   for (size_t i = 0; i < this->hand.size(); i++)
   {
      std::cout << this->hand[i].toString() << " ";
   }
}

/* *********************************************************************
Function Name: printDiscard()
Purpose: Print top of discard pile
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print the top of the discard pile (first card)
Assistance Received: none
********************************************************************* */
void Player::printDiscard()
{
   std::cout << "Current top of discard pile: " << this->topOfDiscard.toString() << "\n";
}

/* *********************************************************************
Function Name: getHand()
Purpose: Returns player's current hand
Parameters:
         none
Return Value: a const vector<Card>, the cards in the player's hand
Local Variables:
         none
Algorithm:
         1) Return the player's hand member variable
Assistance Received: none
********************************************************************* */
std::vector<Card> Player::getHand() const
{
   return this->hand;
}

/* *********************************************************************
Function Name: getHand()
Purpose: Get the players top of discard card
Parameters:
         none
Return Value: a const Card, the viewable card in the discard pile
Local Variables:
         none
Algorithm:
         1) Return the players top of discard card
Assistance Received: none
********************************************************************* */
Card Player::getDiscardCard() const
{
   return this->topOfDiscard;
}

/* *********************************************************************
Function Name: setTopOfDiscard()
Purpose: Set's players top of discard
Parameters:
         Card card, the card to set the top of discard with
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set the topOfDiscard member variable to the card passed in
Assistance Received: none
********************************************************************* */
void Player::setTopOfDiscard(Card card)
{
   this->topOfDiscard = card;
}

/* *********************************************************************
Function Name: findIndexInHand()
Purpose: Find the index the card exists in
Parameters:
         string card, the card we are finding the index of
Return Value: an int, representing the index of where 
   the card passed in exists
Local Variables:
         none
Algorithm:
         1) Set the topOfDiscard member variable to the card passed in
Assistance Received: none
********************************************************************* */
int Player::findIndexInHand(std::string card)
{
   for (size_t i = 0; i < this->hand.size(); i++)
   {
      std::string name = this->hand[i].toString();
      
      // If the card is found
      if (card == name)
      {
         return i;
      }

   }

   // If not found
   std::cout << card << " is not in your hand!\n";
   return -1;
}

/* *********************************************************************
Function Name: discardCard()
Purpose: Return and discard card at index passed in
Parameters:
         int card, the index of the card to delete
Return Value: a Card, the card that was discarded
   the card passed in exists
Local Variables:
         none
Algorithm:
         1) Get the card to discard by accessing the index in the hand
         2) Erase the card at the index
         3) Return the card we removed
Assistance Received: none
********************************************************************* */
Card Player::discardCard(int indexOfCard)
{
   try
   {
      Card discardCard = this->hand[indexOfCard];
      this->hand.erase(this->hand.begin() + indexOfCard);

      return discardCard;
   }
   catch (const std::out_of_range& oor)
   {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
   }
   
}

/* *********************************************************************
Function Name: getCardAtIndex()
Purpose: Return card at index
Parameters:
         int index, the index of card to return
Return Value: a Card, the card at index in player's hand
Local Variables:
         none
Algorithm:
         1) Return the card at the player's hand
Assistance Received: none
********************************************************************* */
Card Player::getCardAtIndex(int index)
{
   return this->hand[index];
}

/* *********************************************************************
Function Name: getPlayerScore()
Purpose: Get player's score
Parameters:
         int index, the index of card to return
Return Value: a const int, the player's current score
Local Variables:
         none
Algorithm:
         1) Return the card at the player's hand
Assistance Received: none
********************************************************************* */
int Player::getPlayerScore() const
{
   return this->score;
}


/* *********************************************************************
Function Name: setPlayerScore()
Purpose: Set player's score
Parameters:
         int score, the score to set player's score to
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set the player's member variable score to the score passed in
Assistance Received: none
********************************************************************* */
void Player::setPlayerScore(int score)
{
   this->score = score;
}

/* *********************************************************************
Function Name: updatePlayerScore()
Purpose: Update (add to) player's score
Parameters:
         vector<Card> remainingCards, the cards remaining after creating
            books and runs
Return Value: none
Local Variables:
         int roundScore, the score for the current round
Algorithm:
         1) Loop through the remaining cards
         2) Add each card's value to the score for the round
         3) Add total to the player's member variable score
Assistance Received: none
********************************************************************* */
void Player::updatePlayerScore(std::vector<Card> remainingCards)
{
   int roundScore = 0;

   for (Card card : remainingCards)
   {
      roundScore += card.getValue();
   }

   std::cout << this->toString() << "'s score for the round: " << roundScore << "\n";
   
   this->score += roundScore;
}

/* *********************************************************************
Function Name: operator <<()
Purpose: Allow us to output player using <<
Parameters:
         ostream& os, a reference to the output stream
         const Player& player, const reference to the Player object
Return Value: ostream&, the output stream
Local Variables:
         none
Algorithm:
         1) Add the player's serialized from to the output stream
         2) Return the output stream
Assistance Received: none
********************************************************************* */
std::ostream& operator << (std::ostream& os, const Player& player)
{
   os << player.serialize();
   return os;
}

/* *********************************************************************
Function Name: sortCards()
Purpose: Sort the cards passed in
Parameters:
         vector<Card> cards, the cards to sort
Return Value: a vector<Card>, the sorted cards passed in
Local Variables:
         none
Algorithm:
         1) Sort the cards
         2) Return them
Assistance Received: none
********************************************************************* */
std::vector<Card> Player::sortCards(std::vector<Card> cards)
{
   std::sort(cards.begin(), cards.end());

   return cards;
}

/* *********************************************************************
Function Name: bestOrder()
Purpose: Find the best order to find combinations in
Parameters:
         vector<Card> cards, the cards to sort
Return Value: a CombinationFinder::order, an enum with the order we 
   should create combinations
Local Variables:
         CombinationFinder finderBooks, finds the single cards remaining
            after making books first and then runs
         CombinationFinder finderRuns, finds the single cards remaining
            after making runs first and then books
         int singlesWithBook, single cards remaining after making books first
         int singlesWithRun, single cards remaining after making runs first
Algorithm:
         1) Find books and then runs
         2) Get single cards remaining
         3) Find runs and then books
         4) Get single cards remaining
         5) Compare the number of single cards in both approaches
         6) If there are less single cards using books first, 
            return enum indicating to make books first
         7) If there are more single cards using books first,
            return enum indicating to make runs first
         8) If they are equal, make runs first 
Assistance Received: none
********************************************************************* */
CombinationFinder::Order Player::bestOrder(std::vector<Card> cards)
{
   // Make books first and get single cards
   CombinationFinder finderBooks;
   finderBooks.findCombinations(CombinationFinder::Order::BOOKS_FIRST);
   int singlesWithBook = finderBooks.getNumberOfSingleCards();

   // Make runs first and get single cards
   CombinationFinder finderRuns;
   finderRuns.findCombinations(CombinationFinder::Order::RUNS_FIRST);
   int singlesWithRun = finderRuns.getNumberOfSingleCards();

   // If there are less single cards with books than run, make books first
   if (singlesWithBook < singlesWithRun)
   {
      return CombinationFinder::Order::BOOKS_FIRST;
   }
   // If there are more single cards with books than run, make runs first
   else if (singlesWithBook > singlesWithRun)
   {
      return CombinationFinder::Order::RUNS_FIRST;
   }
   // If there are an equal number of single cards, choose runs
   else
   {
      return CombinationFinder::Order::RUNS_FIRST;
   }
}

// Check if player can go out
// A player can go out if all the cards in the hand can be arranged in books and runs
bool Player::goOut()
{
   CombinationFinder finder(this->hand);
   CombinationFinder::Order order = bestOrder(this->hand);
   finder.findCombinations(order);

   //TEMP
   //std::vector<Card> wildCardsLeft = finder.getRemainingWilds();

   if (finder.getNumberOfRemainingCards() == 0)
   {
      std::cout << "\n";
      std::cout << this->toString() << " went out!\n";
      this->books = finder.getBooks();
      this->runs = finder.getRuns();

      std::cout << this->toString() << "'s books and runs:\n";
      displayBooksAndRuns();

      return true;
   }

   return false;
}

// Check if player has gone out
bool Player::hasGoneOut()
{
   return this->goneOut ? true : false;
}

// Reset player's gone out status
void Player::resetGoneOutStatus()
{
   this->goneOut = false;
}

// Display all books and runs made after going out
void Player::displayBooksAndRuns()
{
   if (this->books.size() > 0)
   {
      std::cout << "Books:\n";
   }

   for (auto book : books)
   {
      for (auto card : book)
      {
         std::cout << card << " ";
      }
      std::cout << "\n";
   }

   if (this->runs.size() > 0)
   {
      std::cout << "Runs:\n";
   }

   for (auto run : runs)
   {
      for (auto card : run)
      {
         std::cout << card << " ";
      }
      std::cout << "\n";
   }
}