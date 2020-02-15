#include "game.h"

Game::Game()
{
   players[0] = std::shared_ptr<Player>(new Computer());
   players[1] = std::shared_ptr<Player>(new Human());
   std::cout << "        _.+._" << "         _.+._" << "         _.+._" << "         _.+._" << "         _.+._\n";
   std::cout << "      (^\\/^\\/^)" << "     (^\\/^\\/^)" << "     (^\\/^\\/^)" << "     (^\\/^\\/^)" << "     (^\\/^\\/^)\n";
   std::cout << "       \\@*@*@/" << "       \\@*@*@/" << "       \\@*@*@/" << "       \\@*@*@/" << "       \\@*@*@/\n";
   std::cout << "       {_____}" << "       {_____}" << "       {_____}" << "       {_____}" << "       {_____}\n";
   std::cout << "\n\t\t\t   Welcome to Five Crowns\n\n";
}

/* *********************************************************************
Function Name: startGame()
Purpose: Start the game
Parameters:
         none
Return Value: none
Local Variables:
         string startChoice, start a new game, load a game file,
         or exit game
Algorithm:
         1) Seed a random time
         2) Get the start choice
         3) Start a new game, load a game file, or exit game
         depending on input
Assistance Received: none
********************************************************************* */
void Game::startGame()
{
   // Seed random time
   srand(unsigned(time(NULL)));
   startMenu();
   std::string startChoice = getStartChoice();

   while (startChoice != "1" && startChoice != "2" && startChoice != "3")
   {
      startMenu();
      startChoice = getStartChoice();
   }
   // Start new game
   if (startChoice == "1")
   {
      firstRound();
      /*nextRound(this->roundNumber);*/
   }
   // Load game
   else if (startChoice == "2")
   {
      loadGameFile();
      //loadGameTest();
   }
   else if (startChoice == "3")
   {
      return;
   }
   else
   {
      std::cout << "Something went wrong\n";
   }
}

/* *********************************************************************
Function Name: startMenu()
Purpose: Print the start menu
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print start game options
Assistance Received: none
********************************************************************* */
void Game::startMenu()
{
   std::cout << "1. Start new game\n";
   std::cout << "2. Load game file\n";
   std::cout << "3. Exit\n";
}


/* *********************************************************************
Function Name: firstRound()
Purpose: Play the first round of the game
Parameters:
         none
Return Value: none
Local Variables:
         Round round, the current round
Algorithm:
         1) Create a new Round object
         2) Deal cards to players
         3) Set discard pile and top of discard pile
         4) Determine first player
         5) Play while no player has gone out
Assistance Received: none
********************************************************************* */
void Game::firstRound()
{
   // Create new round object
   Round newRound(this->roundNumber);

   // Set the current Round object
   this->round = newRound;

   // Deal cards to all players
   dealCards();

   // Discard first card from draw pile and add to discard pile
   Card discardCard = this->round.drawDeck();
   setTopOfDiscard(discardCard);
   this->round.discardCard(discardCard);

   // Decide who goes first
   setFirstPlayer();
   int firstPlayer = this->getFirstPlayer();

   // While no one has gone out, play the next turn
   while (!this->hasPlayerGoneOut)
   {
      nextTurn();
   }


}

/* *********************************************************************
Function Name: dealCards()
Purpose: Deal cards to all players based on the current round
Parameters:
         none
Return Value: none
Local Variables:
         vector<vector<Card>> hands, the hands each player will
         have
Algorithm:
         1) Clear players current cards
         2) Get cards to deal from Round
         3) Set each players hand
Assistance Received: none
********************************************************************* */
void Game::dealCards()
{
   // Clear players cards and discard card
   resetPlayerCards();

   std::vector<std::vector<Card>> hands = this->round.dealCards(this->roundNumber, this->PLAYER_COUNT);
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      this->players[i]->setHand(hands[i]);
      this->players[i]->setHand(hands[i]);
   }
}

/* *********************************************************************
Function Name: resetPlayerCards()
Purpose: Resets all the cards the player has
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through all players
         2) Clear their hand
         3) Reset their discard card
Assistance Received: none
********************************************************************* */
void Game::resetPlayerCards()
{
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      this->players[i]->clearHand();
      this->players[i]->resetDiscardCard();
   }
}

/* *********************************************************************
Function Name: nextTurn()
Purpose: Plays the next turn of the game
Parameters:
         none
Return Value: none
Local Variables:
         int gameChoice, the choice the player makes: save, move,
         help, or quit
Algorithm:
         1) Print the current game stats
         2) Set the current player
         3) Get the game choice
         4) Do action based on choice
         5) Increment current turn number
Assistance Received: none
********************************************************************* */
// Play the next turn of the round
void Game::nextTurn()
{
   // Print current game stats
   printGameStats();

   // Set current player
   setCurrentPlayer(turnNumber);

   // Ask player what move they want to make
   int gameChoice = this->players[this->currentPlayer]->chooseGameOption();

   // Save game
   if (gameChoice == 1)
   {
      // Save game to file and exit game
      serializeGame();
      exit(EXIT_SUCCESS);
   }
   // Make a move
   else if (gameChoice == 2)
   {
      // Move player
      movePlayer();
   }
   // Ask computer for help on what move you should make
   else if (gameChoice == 3)
   {
      askComputerForHelp(Computer::Help::DRAW_HELP);
      movePlayer();
   }
   // Quit game
   else
   {
      exit(EXIT_SUCCESS);
   }

   // MAYBE DELETE BECAUSE ITS NOT NEEDED
   // Print current game stats
   printGameStats();

   // Increment the turn
   this->turnNumber++;
}

/* *********************************************************************
Function Name: lastTurn()
Purpose: Plays the last turn of the round
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Increment turn number
         2) Set the current player
         3) Move player
         4) Update player scores
Assistance Received: none
********************************************************************* */
void Game::lastTurn()
{
   turnNumber++;
   //setCurrentPlayer(turnNumber);

   std::cout << "\n" << this->players[this->currentPlayer]->toString() << "'s books and runs:\n";
   this->players[this->currentPlayer]->displayBooksAndRuns();

   std::cout << "\n>>>>>>>>>> Last turn to try and minimize score! <<<<<<<<<<\n\n";
   nextTurn();

   printGameStats();

   // Update players scores
   updatePlayerScores();

   //this->roundNumber = this->roundNumber + 1;
}


/* *********************************************************************
Function Name: updatePlayerScores()
Purpose: Updates scores of all players
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through all players
         2) If player has not gone out, update their score
         3) Otherwise their score remains the same
Assistance Received: none
********************************************************************* */
void Game::updatePlayerScores()
{
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      std::vector<Card> hand = players[i]->getHand();
      CombinationFinder finder(hand);
      CombinationFinder::Order order = players[i]->bestOrder(hand);
      finder.findCombinations(order);
      finder.combineRemainingCards();

      std::vector<Card> remainingCards = finder.retrieveRemainingCards();

      this->players[i]->updatePlayerScore(remainingCards);
   }
}

/* *********************************************************************
Function Name: nextRound()
Purpose: Play the next round of the game
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) If we played all rounds, determine the winner and exit
         2) Prepare the round
         3) Create new Round object
         4) Deal cards
         5) Set discard card
         6) While no player has gone out, keep playing
         7) Update player scores
Assistance Received: none
********************************************************************* */
void Game::nextRound()
{
   this->currentPlayer;
   this->firstPlayerOfNextRound;

   this->goneOutCount = 0;

   // Check to see if we've played the last round
   if (this->roundNumber > 11)
   {
      printWinner();
      std::cin.get();
      exit(EXIT_SUCCESS);
   }

   // Prepare the round
   prepareRound();

   // Create new round object
   Round newRound(this->roundNumber);

   // Set the current Round object
   this->round = newRound;

   // Deal cards to all players
   dealCards();

   // Discard first card from draw pile and add to discard pile
   Card discardCard = this->round.drawDeck();
   setTopOfDiscard(discardCard);
   this->round.discardCard(discardCard);

   // While no one has gone out, play the next turn
   while (!this->hasPlayerGoneOut)
   {
      nextTurn();
   }

   // Update players scores
   updatePlayerScores();
}

/* *********************************************************************
Function Name: prepareRound()
Purpose: Prepare the round before playing the next
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Reset winner status
         2) Reset player gone out status
         3) Set player one
         4) Reset turn number
Assistance Received: none
********************************************************************* */
void Game::prepareRound()
{
   // Reset winner status
   this->hasPlayerGoneOut = false;

   // Reset player gone out status
   resetPlayerStatus();

   // Set player to play first to the first player of next round
   this->playerOne = this->firstPlayerOfNextRound;

   // Reset turn number
   this->turnNumber = 0;
}


/* *********************************************************************
Function Name: resetPlayerStatus()
Purpose: Resets the players gone out status
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through all players
         2) Reset player gone out status
Assistance Received: none
********************************************************************* */
void Game::resetPlayerStatus()
{
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      this->players[i]->resetGoneOutStatus();
   }
}

/* *********************************************************************
Function Name: continueRound()
Purpose: Continues the round when loading a game save file
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) While no player has gone out, play next turn
         2) Update players scores
Assistance Received: none
********************************************************************* */
void Game::continueRound()
{
   this->currentPlayer;
   this->firstPlayerOfNextRound;

   // While no one has gone out, play the next turn
   while (!this->hasPlayerGoneOut)
   {
      nextTurn();
   }

   // Update players scores
   updatePlayerScores();
}


/* *********************************************************************
Function Name: setFirstPlayer()
Purpose: Sets the player to go first on the first turn
Parameters:
         none
Return Value: none
Local Variables:
         string headTails, determine if heads or tails was entered
Algorithm:
         1) Get user input for heads or tails
         2) Randomly choose which player goes first
         3) Set playerOne member variable to random choice
Assistance Received: none
********************************************************************* */
void Game::setFirstPlayer()
{
   std::string headsTails = "f";
   std::cout << "You will decide who goes first: heads or tails?\n";
   std::getline(std::cin, headsTails);

   transform(headsTails.begin(), headsTails.end(), headsTails.begin(), ::toupper);
   while (headsTails != "T" && headsTails != "H")
   {
      std::cout << "H or T\n";
      std::getline(std::cin, headsTails);
      transform(headsTails.begin(), headsTails.end(), headsTails.begin(), ::toupper);
   }

   playerOne = rand() % PLAYER_COUNT;
   
   if (playerOne == 0)
   {
      std::cout << "\nCOMPUTER will play first\n\n";
   }
   else if (playerOne == 1)
   {
      std::cout << "\nHUMAN will play first\n\n";
   }
   
   this->playerOne = playerOne; 
}

/* *********************************************************************
Function Name: getFirstPlayer()
Purpose: Gets the player to play first
Parameters:
         none
Return Value: a const int, the index of the player to play first
Local Variables:
         string headTails, determine if heads or tails was entered
Algorithm:
         1) Return member variable playerOne
Assistance Received: none
********************************************************************* */
int Game::getFirstPlayer() const
{
   return this->playerOne;
}

/* *********************************************************************
Function Name: setCurrentPlayer()
Purpose: Set the current player whose turn it is
Parameters:
         int turn, the turn number we're currently on
Return Value: none
Local Variables:
         none
Algorithm:
         1) Add turn number and first player together
         2) Modulus that result with the total number of players
         3) Return that value
Assistance Received: none
********************************************************************* */
void Game::setCurrentPlayer(int turn)
{
   this->currentPlayer = (turn + this->playerOne) % this->PLAYER_COUNT;
}

/* *********************************************************************
Function Name: getStartChoice()
Purpose: Get the start choice user chose
Parameters:
         none
Return Value: a const string, the choice they made "1", "2", "3"
Local Variables:
         string startChoice, to store choice they made
Algorithm:
         1) Get the start choice
         2) Return it
Assistance Received: none
********************************************************************* */
std::string Game::getStartChoice() const
{
   std::string startChoice;
   std::getline(std::cin, startChoice);

   return startChoice;
}


/* *********************************************************************
Function Name: printGameStats()
Purpose: Print current game stats
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print roundNumber 
         2) Print each player and their hands and score
         3) Print top of discard pile
         4) Print the draw pile
Assistance Received: none
********************************************************************* */
void Game::printGameStats()
{
   std::cout << "Current round: " << this->roundNumber << "\n";
   
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      std::cout << this->players[i]->serialize() << "\n";
   }

   this->players[0]->printDiscard();
   std::cout << "Draw pile: ";
   
   this->round.printDeck();
   std::cout << "\n\n";
}

/* *********************************************************************
Function Name: movePlayer()
Purpose: Move the current player
Parameters:
         none
Return Value: none
Local Variables:
         int moveChoice, what move they want to make: draw from 
         discard pile or draw from drawing pile
Algorithm:
         1) Get move choice
         2) Get top of draw/discard pile
         3) Add to players hand
         4) Get the card they want to discard
         5) Check if player can go out
Assistance Received: none
********************************************************************* */
void Game::movePlayer()
{
   int moveChoice;
   
   do {
      try
      {
         moveChoice = players[this->currentPlayer]->move();
      }
      catch (std::out_of_range)
      {
         //std::cout << "DECK IS EMPTY!\n";
      }
   } while (moveChoice < 1 || moveChoice > 2);

   // Check to see if deck is empty
   if (isDeckEmpty())
   {
      moveChoice = static_cast<int>(Player::moveOption::DRAW_DISCARD);
      //moveChoice = 2;
   }

   // If we are drawing from deck, take from top of deck and add to players hand
   if (moveChoice == 1)
   {
      // Draw card from deck drawing pile
      Card topOfDeck = this->round.drawDeck();

      // Add to hand
      players[this->currentPlayer]->addToHand(topOfDeck);
   }
   // If we are drawing from discard, take from top of discard and add to players hand
   else if (moveChoice == 2)
   {
      // Draw card from deck discard pile
      Card topOfDiscard = this->round.drawDiscard();

      Card newTopOfDiscard = this->round.getTopOfDiscardPile();
      setTopOfDiscard(newTopOfDiscard);

      // Add to hand
      players[this->currentPlayer]->addToHand(topOfDiscard);
   }
   else if (moveChoice == 3)
   {

   }

   // Get discard card from player
   getCardToDiscard();

   // Check if player can go out
   bool goneOut = players[this->currentPlayer]->goOut();
   if (goneOut && this->goneOutCount < PLAYER_COUNT)
   {
      this->goneOutCount++;

      // Set first player of next round to current player
      this->firstPlayerOfNextRound = this->currentPlayer;

      // Play the last turn, increment turn and start next round
      lastTurn();
      this->hasPlayerGoneOut = true;
      this->roundNumber++;
      nextRound();
   }
}

// Check if the deck is empty (no cards remaining in draw pile)
bool Game::isDeckEmpty()
{
   return (this->round.isDrawingPileEmpty() ? true : false);
}

/* *********************************************************************
Function Name: getCardToDiscard()
Purpose: Get the card player wants to discard
Parameters:
         none
Return Value: none
Local Variables:
         string nameOfCard, the card they want to remove
         int indexOfCard, the index of that card
         Card cardToDiscard
Algorithm:
         1) Print game stats
         2) Get name of card to discard
         3) Get the index of that card
         4) Validate input
         5) Discard the card
         6) Add to discard pile and set player's discard card
Assistance Received: none
********************************************************************* */
void Game::getCardToDiscard()
{
   try
   {
      // Print current game stats
      printGameStats();

      std::pair<bool, std::string> nameOfCardAndHelp = this->players[this->currentPlayer]->getCardToDiscard();

      if (nameOfCardAndHelp.first)
      {
         askComputerForHelp(Computer::Help::DISCARD_HELP);
         //getCardToDiscard();
      }

      std::string nameOfCard = nameOfCardAndHelp.second;

      // Get index in players hand of card
      int indexOfCard = this->players[this->currentPlayer]->findIndexInHand(nameOfCard);

      // While the card is not found, get a new one from player
      while (indexOfCard == -1)
      {
         nameOfCardAndHelp = this->players[this->currentPlayer]->getCardToDiscard();
         indexOfCard = this->players[this->currentPlayer]->findIndexInHand(nameOfCardAndHelp.second);
      }

      // Discard the card and add to discard pile
      Card cardToDiscard = this->players[this->currentPlayer]->getCardAtIndex(indexOfCard);

      // Discard players card
      this->players[this->currentPlayer]->discardCard(indexOfCard);

      // Add to discard pile
      this->round.discardCard(cardToDiscard);

      // Set players top of discard card
      setTopOfDiscard(cardToDiscard);
   }
   catch (const std::out_of_range& oor)
   {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
   }
   
}

/* *********************************************************************
Function Name: askComputerForHelp()
Purpose: Get suggestions from Computer on what move to make
Parameters:
         none
Return Value: none
Local Variables:
         vector<Card> hand, current player's hand
         Card discardCard, the current player's discard card
Algorithm:
         1) Get current player's hand
         2) Get current player's discard card
         3) Call Computer's help function and pass in cards
Assistance Received: none
********************************************************************* */
void Game::askComputerForHelp(Computer::Help helpType)
{
   // Get the current players hand
   std::vector<Card> hand = this->players[this->currentPlayer]->getHand();

   // Get the current players discard card
   Card discardCard = this->players[this->currentPlayer]->getDiscardCard();

   // Ask computer for help
   Computer::help(hand, discardCard, helpType);
}

/* *********************************************************************
Function Name: setPlayerScore()
Purpose: Set the players score
Parameters:
         int player, the player that will have its score set
         int score, the score of the player
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set players score to value passed in
Assistance Received: none
********************************************************************* */
void Game::setPlayerScore(int player, int score)
{
   this->players[player]->setPlayerScore(score);
}


/* *********************************************************************
Function Name: setPlayerHand()
Purpose: Set the players hand
Parameters:
         int player, the player that will have its hand set
         vector<Card> hand, the hand of the player
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set players hand to cards passed in
Assistance Received: none
********************************************************************* */
void Game::setPlayerHand(int player, std::vector<Card> hand)
{
   this->players[player]->setHand(hand);
}

/* *********************************************************************
Function Name: setDrawPile()
Purpose: Sets the rounds draw pile
Parameters:
         vector<Card> drawPile, the draw pile to set
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set the rounds draw pile to draw pile passed in
Assistance Received: none
********************************************************************* */
void Game::setDrawPile(std::vector<Card> drawPile)
{
   this->round.setDrawPile(drawPile);
}

/* *********************************************************************
Function Name: setDiscardPile()
Purpose: Sets the rounds discard pile
Parameters:
         deque<Card> discardPile, the discard pile to set
Return Value: none
Local Variables:
         none
Algorithm:
         1) Set the rounds discard pile to discard pile passed in
Assistance Received: none
********************************************************************* */
void Game::setDiscardPile(std::deque<Card> discardPile)
{
   this->round.setDiscardPile(discardPile);
}

/* *********************************************************************
Function Name: setTopOfDiscard()
Purpose: Sets player top of discard card
Parameters:
         Card topOfDiscard, card to set player's top of discard card
         to
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through all players
         2) Set each player's top of discard card to card passed in
Assistance Received: none
********************************************************************* */
void Game::setTopOfDiscard(Card topOfDiscard)
{
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      players[i]->setTopOfDiscard(topOfDiscard);
   }
}


/* *********************************************************************
Function Name: loadGameFile()
Purpose: Load a game save file into game and continue playing
Parameters:
         Card topOfDiscard, card to set player's top of discard card
         to
Return Value: none
Local Variables:
         GameFile load, object that stores all game values
         bool fail, check to see if file opened succesfully
         int gameRound, round from save file
         int computerScore, computer score from save file
         int humanScore, human score from save file
         int nextPlayer, next player from save file
         vector<Card> computerHand, computer hand from save file
         vector<Card> humanHand, human hand from save file
         vector<Card> drawPile, draw pile from save file
         deque<Card> discardPile, discard pile from save file

Algorithm:
         1) Open save file
         2) Set all values from save file
         3) Continue the round
Assistance Received: none
********************************************************************* */
void Game::loadGameFile()
{
   // Get game file and attempt to open it
   GameFile load;
   bool fail = load.openFile();
   
   // If the file failed to open, get the game option again
   if (fail)
   {
      this->startGame();
   }

   // Parse the file we opened
   load.parseFile();

   int gameRound = load.getGameRound();
   int computerScore = load.getComputerScore();
   int humanScore = load.getHumanScore();
   int nextPlayer = load.getNextPlayer();

   std::vector<Card> computerHand = load.getComputerHand();
   std::vector<Card> humanHand = load.getHumanHand();
   std::vector<Card> drawPile = load.getDrawPile();

   std::deque<Card> discardPile = load.getDiscardPile();

   this->currentPlayer = load.getNextPlayer();

   // Set game state
   // 1. Set current round
   this->roundNumber = gameRound;

   // 2. Set scores
   this->setPlayerScore(0, computerScore);
   this->setPlayerScore(1, humanScore);

   // 3. Set player hands
   this->players[0]->setHand(computerHand);
   this->players[1]->setHand(humanHand);

   // 4. Set Round object and set drawing pile and discard pile
   Round round(drawPile, discardPile);
   this->round = round;


   // Set current turn number
   this->turnNumber = currentPlayer;

   // 5. Set player top of hand
   setTopOfDiscard(discardPile[0]);
   
   // Continue round
   continueRound();
}


/* *********************************************************************
Function Name: serializeGame()
Purpose: Save the current games state to a file
Parameters:
         none
Return Value: none
Local Variables:
         string gameState, the current state of the game
Algorithm:
         1) Add round number to gameState
         2) Add player hand and scores to gameState
         3) Add draw pile and discard pile to gameState
         4) Save the game
Assistance Received: none
********************************************************************* */
void Game::serializeGame()
{
   // Add round number to game state
   std::string gameState = "Round: ";
   gameState += std::to_string(roundNumber) + "\n\n";

   // Add players, their scores, and hands to game state
   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      gameState += this->players[i]->serialize();
      gameState += "\n\n";
   }
   gameState += "\n";

   // Add draw pile to game state
   // Add discard pile to game state
   gameState += round.serializeDeck() + "\n\n";

   // Add next player to game state
   gameState += "Next Player: " + this->players[(this->currentPlayer + 1) % PLAYER_COUNT]->toString();

   // Save the game
   GameFile save;
   save.saveGameToFile(gameState);
}

/* *********************************************************************
Function Name: determineWinner()
Purpose: Determine the winner of the game
Parameters:
         none
Return Value: an int, which is the index of the player who won
Local Variables:
         vector<pair<int, int>> scores, keep track of which player
         has what score
         int winner, the winner of the game
Algorithm:
         1) While no player has gone out, play next turn
         2) Update players scores
Assistance Received: none
********************************************************************* */
int Game::determineWinner()
{
   // Check if there is a tie
   if (isTie())
   {
      return -1;
   }

   // Get all player scores
   // Pair of player score and their index in player array
   std::vector<std::pair<int, int>> scores;

   for (int i = 0; i < PLAYER_COUNT; i++)
   {
      scores.push_back(std::make_pair(players[i]->getPlayerScore(), i));
   }

   // Sort scores
   sort(scores.begin(), scores.end());

   for (size_t i = 0; i < scores.size(); i++)
   {
      std::cout << scores[i].first << " "
         << scores[i].second << "\n";
   }

   // Since it's sorted ascending, the winner will be the first one
   int winner = scores[0].second;

   return winner;
}


/* *********************************************************************
Function Name: isTie()
Purpose: Determine if game resulted in a tie
Parameters:
         none
Return Value: a bool determining if there is a tie or not
Local Variables:
         int sameScoreCheck, check if all players have same score
         int firstPlayerScore, score of first player
Algorithm:
         1) Set first players score
         2) Loop through rest of players
         3) If score is the same for all, we have a tie, return true
         4) Return false
Assistance Received: none
********************************************************************* */
bool Game::isTie()
{
   int sameScoreCheck = 1;
   int firstPlayerScore = players[0]->getPlayerScore();

   for (int i = 1; i < PLAYER_COUNT; i++)
   {
      if (sameScoreCheck == PLAYER_COUNT)
      {
         return true;
      }

      if (players[i]->getPlayerScore() == firstPlayerScore)
      {
         sameScoreCheck++;
      }
   }

   return false;
}

/* *********************************************************************
Function Name: printWinner()
Purpose: Prints the winner of the game
Parameters:
         none
Return Value: none
Local Variables:
         int winner, the winner of the game
Algorithm:
         1) Determine the winner
         2) Print who won or tied
Assistance Received: none
********************************************************************* */
void Game::printWinner()
{
   int winner = determineWinner();
   int loser = (winner + 1) % PLAYER_COUNT;

   if (winner == -1)
   {
      for (int i = 0; i < PLAYER_COUNT; i++)
      {
         std::cout << players[i]->toString() << " tied with a score of " << players[i]->getPlayerScore() << "\n";
      }
   }
   else
   {
      std::cout << players[winner]->toString() << " is the winner with a score of " << players[winner]->getPlayerScore() << "\n";
      std::cout << players[loser]->toString() << " is the loser with a score of " << players[loser]->getPlayerScore() << "\n";
   }
   std::cin.get();
}