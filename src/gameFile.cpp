#include "gameFile.h"


/* *********************************************************************
Function Name: openFile()
Purpose: Try and open user specified file
Parameters:
         none
Return Value: a bool, whether or not file was successfull opened
Local Variables:
         string gameFileName, name of game file
Algorithm:
         1) Open file
         2) If file failed, return true
         3) Otherwise return false
Assistance Received: none
********************************************************************* */
bool GameFile::openFile()
{
   std::string gameFileName = getGameFileName();

   loadFile.open(gameFileName);

   // Abort if file can't be opened
   // Potentially change so that user can try again
   if (!loadFile)
   {
      std::cerr << "Game file " << gameFileName << " could not be opened\n";
      return true;
   }

   return false;
}

/* *********************************************************************
Function Name: getGameFileName()
Purpose: Get name of game file
Parameters:
         none
Return Value: a string, the name of the file
Local Variables:
         string gameFile, name of game file
Algorithm:
         1) Get name of game file
         2) Return name of game file
Assistance Received: none
********************************************************************* */
std::string GameFile::getGameFileName()
{
   std::string gameFile;
   std::cout << "Enter name of game file: ";
   std::getline(std::cin, gameFile);

   return gameFile;
}


/* *********************************************************************
Function Name: parseFile()
Purpose: Get name of game file
Parameters:
         none
Return Value: none
Local Variables:
         string line, the line of the file
         int colonLocation, location on line where there is a colon
         string key, the key of the line
         string value, the value of the line
         regex regex("\\s+"), to remove whitespaces
Algorithm:
         1) For each line, get the key and value associated
         2) Add to unordered map member variable where the key is
         the variable (i.e. score, hand, etc) and the value is
         what's after the colon : (i.e. "1", "S6 S5 S4", etc)
         3) Based on these construct the cards and values
Assistance Received: none
********************************************************************* */
void GameFile::parseFile()
{
   std::string line;
   int colonLocation;
   std::string key;
   std::string value;

   // To remove whitespaces
   std::regex regex("\\s+");

   // While not at end of file
   while (!loadFile.eof())
   {
      // Get the current line
      getline(loadFile, line);

      // If it's not a whitespace line, get position of :
      if (!std::all_of(line.begin(), line.end(), isspace))
      {
         // Get location of colon
         colonLocation = line.find(":");
         key = line.substr(0, colonLocation);

         // Remove all whitespace from key if it begins with a white space
         key = std::regex_replace(key, regex, "");
         value = line.substr(colonLocation + 1, line.length());

         // Delete extra whitespace if it exists
         if (value[0] == ' ')
         {
            value.erase(0, 1);
         }

         // If we come across Scores or Hand again, this is the Human's score and hand
         if (this->gameValues.count(key) > 0)
         {
            key.insert(0, "Human");
         }

         // Add value to hashmap
         this->gameValues[key] = value;
      }
   }

   parseInt();
   parseCards();
   loadFile.close();
}


/* *********************************************************************
Function Name: parseInt()
Purpose: Convert all game file values to integers
Parameters:
         none
Return Value: none
Local Variables:
         string nextPlayerString, next player in round
Algorithm:
         1) Parse gameRound to int
         2) Parse computerScore to int
         3) Parse humanScore to int
         4) Parse nextPlayer to int
Assistance Received: none
********************************************************************* */
void GameFile::parseInt()
{
   this->gameRound = stoi(gameValues.at("Round"));
   this->computerScore = stoi(gameValues.at("Score"));
   this->humanScore = stoi(gameValues.at("HumanScore"));

   std::string nextPlayerString = gameValues.at("NextPlayer");
   this->nextPlayer = (nextPlayerString == "Computer") ? 0 : 1;
   //int x;
}


/* *********************************************************************
Function Name: parseCards()
Purpose: Parse the list of cards from the game file
Parameters:
         none
Return Value: none
Local Variables:
Algorithm:
         1) Get all card values from game file
         2) Create vector of strings from cards
         3) Create vector of cards from each vector of strings
Assistance Received: https://en.cppreference.com/w/cpp/regex/regex_token_iterator
********************************************************************* */
void GameFile::parseCards()
{
   std::string computerHandString = gameValues.at("Hand");
   std::string humanHandString = gameValues.at("HumanHand");
   std::string drawPileString = gameValues.at("DrawPile");
   std::string discardPileString = gameValues.at("DiscardPile");

   // To remove whitespaces
   std::regex regex("\\s+");

   // Construct a vector of strings from the computer's hand
   std::vector<std::string> computerHandVString
   {
      std::sregex_token_iterator(computerHandString.begin(), computerHandString.end(), regex, -1), {}
   };

   // Construct a vector of strings from the human's hand
   std::vector<std::string> humanHandVString
   {
      std::sregex_token_iterator(humanHandString.begin(), humanHandString.end(), regex, -1), {}
   };

   // Construct vector of strings from draw pile
   std::vector<std::string> drawPileVString
   {
      std::sregex_token_iterator(drawPileString.begin(), drawPileString.end(), regex, -1), {}
   };

   // Construct vector of strings from discard pile
   std::vector<std::string> discardPileVString
   {
      std::sregex_token_iterator(discardPileString.begin(), discardPileString.end(), regex, -1), {}
   };

   // Create the list of cards
   this->computerHand = createVectorOfCards(computerHandVString);
   this->humanHand = createVectorOfCards(humanHandVString);
   this->drawPile = createVectorOfCards(drawPileVString);
   this->discardPile = createDequeOfCards(discardPileVString);
}

/* *********************************************************************
Function Name: createVectorOfCards()
Purpose: Create a vector of cards from the game file
Parameters:
         vector<string> cardStrings, strings to convert to cards
Return Value: vector<Card>, the cards we made from vector of strings
Local Variables:
         vector<Card> cards, card to return 
Algorithm:
         1) Loop through all cards (strings)
         2) Create a Card object for each
         3) Push to cards
         4) Return cards
Assistance Received: none
********************************************************************* */
std::vector<Card> GameFile::createVectorOfCards(std::vector<std::string> cardStrings)
{
   std::vector<Card> cards;
   for (std::vector<std::string>::const_iterator it = cardStrings.begin(); it != cardStrings.end(); ++it)
   {
      //std::cout << *it << "\n";
      Card card = Card((*it), this->gameRound);
      cards.push_back(card);
   }

   return cards;
}

/* *********************************************************************
Function Name: createDequeOfCards()
Purpose: Create a deque of cards from the game file
Parameters:
         vector<string> cardStrings, strings to convert to cards
Return Value: deque<Card>, the cards we made from vector of strings
Local Variables:
         deque<Card> cards, card to return
Algorithm:
         1) Loop through all cards (strings)
         2) Create a Card object for each
         3) Push to cards
         4) Return cards
Assistance Received: none
********************************************************************* */
std::deque<Card> GameFile::createDequeOfCards(std::vector<std::string> cardStrings)
{
   std::deque<Card> cards;
   for (std::vector<std::string>::const_iterator it = cardStrings.begin(); it != cardStrings.end(); ++it)
   {
      //std::cout << *it << "\n";
      Card card = Card((*it), this->gameRound);
      cards.push_back(card);
   }

   return cards;
}

/* *********************************************************************
Function Name: getGameRound()
Purpose: Get the game round
Parameters:
         none
Return Value: a const int, the game round
Local Variables:
         none
Algorithm:
         1) Return the game round
Assistance Received: none
********************************************************************* */
int GameFile::getGameRound() const
{
   return this->gameRound;
}


/* *********************************************************************
Function Name: getComputerScore()
Purpose: Get the computer score
Parameters:
         none
Return Value: a const int, the computer score
Local Variables:
         none
Algorithm:
         1) Return the computer score
Assistance Received: none
********************************************************************* */
int GameFile::getComputerScore() const
{
   return this->computerScore;
}


/* *********************************************************************
Function Name: getHumanScore()
Purpose: Get the human score
Parameters:
         none
Return Value: a const int, the human score
Local Variables:
         none
Algorithm:
         1) Return the human score
Assistance Received: none
********************************************************************* */
int GameFile::getHumanScore() const
{
   return this->humanScore;
}

/* *********************************************************************
Function Name: getNextPlayer()
Purpose: Get the next player
Parameters:
         none
Return Value: a const int, the next player
Local Variables:
         none
Algorithm:
         1) Return the next player
Assistance Received: none
********************************************************************* */
int GameFile::getNextPlayer() const
{
   return this->nextPlayer;
}

/* *********************************************************************
Function Name: getComputerHand()
Purpose: Get the computers hand
Parameters:
         none
Return Value: const vector<Card>, the computers hand
Local Variables:
         none
Algorithm:
         1) Return the computers hand
Assistance Received: none
********************************************************************* */
std::vector<Card> GameFile::getComputerHand() const
{
   return this->computerHand;
}

/* *********************************************************************
Function Name: getHumanHand()
Purpose: Get the humans hand
Parameters:
         none
Return Value: const vector<Card>, the humans hand
Local Variables:
         none
Algorithm:
         1) Return the human hand
Assistance Received: none
********************************************************************* */
std::vector<Card> GameFile::getHumanHand() const
{
   return this->humanHand;
}

/* *********************************************************************
Function Name: getDrawPile()
Purpose: Get the draw pile
Parameters:
         none
Return Value: const vector<Card>, the draw pile
Local Variables:
         none
Algorithm:
         1) Return the draw pile 
Assistance Received: none
********************************************************************* */
std::vector<Card> GameFile::getDrawPile() const
{
   return this->drawPile;
}

/* *********************************************************************
Function Name: getDiscardPile()
Purpose: Get the discard pile
Parameters:
         none
Return Value: const deque<Card>, the discard pile
Local Variables:
         none
Algorithm:
         1) Return the discard pile
Assistance Received: none
********************************************************************* */
std::deque<Card> GameFile::getDiscardPile() const
{
   return this->discardPile;
}

/* *********************************************************************
Function Name: saveGameToFile()
Purpose: Saves the current game state into user specified file
Parameters:
         string gameState, the current state of the game
Return Value: none
Local Variables:
         string fileName, name of the file
Algorithm:
         1) Get file to save game to
         2) Open file
         3) If file is open, save to file
Assistance Received: none
********************************************************************* */
void GameFile::saveGameToFile(std::string gameState)
{   
   std::string fileName;
   std::cout << "Enter name of file to save game to: ";
   
   std::getline(std::cin, fileName);

   saveFile.open(fileName);
   if (saveFile.is_open())
   {
      saveFile << gameState;
      saveFile.close();
   }
   else
   {
      std::cout << "Invalid file name!\n";
      saveGameToFile(gameState);
   }
}