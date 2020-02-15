#include "human.h"

/* *********************************************************************
Function Name: chooseGameOption()
Purpose: Choose which game option to do
Parameters:
         none
Return Value: none
Local Variables:
         string gameChoice, the choice to make
Algorithm:
         1) Get game choice
         2) If choice is not 1, 2, 3, or 4 ask again
         3) Return game choice
Assistance Received: none
********************************************************************* */
int Human::chooseGameOption()
{
   //printMenu();
   std::string gameChoice;

   while (gameChoice != "1" && gameChoice != "2" && gameChoice != "3" && gameChoice != "4")
   {
      printMenu();
      // Get size of buffer and ignore all of the characters in them, or the first new line
      std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n'); 
      std::getline(std::cin, gameChoice);
   }

   if (gameChoice == "1")
   {
      return static_cast<int>(Player::gameOption::SAVE_GAME);
      //return 1;
   }
   else if (gameChoice == "2")
   {
      return static_cast<int>(Player::gameOption::MAKE_MOVE);
      //return 2;
   }
   else if (gameChoice == "3")
   {
      return static_cast<int>(Player::gameOption::ASK_HELP);
      //return 3;
   }
   else if (gameChoice == "4")
   {
      return static_cast<int>(Player::gameOption::QUIT_GAME);
      //return 4;
   }
   else
   {
      return -1;
   }

}

/* *********************************************************************
Function Name: move()
Purpose: Get the move choice from Human. Draw from draw pile or discard pile
Parameters:
         none
Return Value: none
Local Variables:
         int moveChoice, the choice the Human made
Algorithm:
         1) Get game choice
         2) If choice is not 1, 2, 3, or 4 ask again
         3) Return game choice
Assistance Received: none
********************************************************************* */
int Human::move()
{
   printMoveOption();
   int moveChoice;

   while (!(std::cin >> moveChoice))
   {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      printMoveOption();
   }

   if (moveChoice == 1)
   {
      return static_cast<int>(Player::moveOption::DRAW_DECK);
      //return 1;
   }
   else if (moveChoice == 2)
   {
      return static_cast<int>(Player::moveOption::DRAW_DISCARD);
      //return 2;
   }
   else
   {
      return -1;
   }
}

/* *********************************************************************
Function Name: printMenu()
Purpose: Print the menu options for the turn for the Human player
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print the options for Human
            1. Save game
            2. Make move
            3. Ask help
            4. Quit
Assistance Received: none
********************************************************************* */
void Human::printMenu()
{
   std::cout << 
      "1. Save the game\n" <<
      "2. Make a move\n" << 
      "3. Ask for help\n" <<
      "4. Quit the game\n";
}

/* *********************************************************************
Function Name: getCardToDiscard()
Purpose: Print the menu options for the turn for the Human player
Parameters:
         none
Return Value: a pair<bool, string>, whether the player is asking for help
   and the card the player is discarding
Local Variables:
         pair<bool, string> cardAndHelp, whether they are discarding,
            and the card name
         string nameOfCard
Algorithm:
         1) Ask Human if they are discarding a card or asking for help
         2) Validate input
         3) If they ask for help, return a pair containing true and
            an empty string for the card
         4) If they choose to discard, get the name of the card they
            are discarding
         5) Return a pair containing false and the name of the card 
            they entered
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Human::getCardToDiscard()
{
   std::string option = "";
   
   std::cout << "1. Discard card\n";
   std::cout << "2. Ask for help\n";

   while (!(std::cin >> option))
   {
      //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "1. Discard card\n";
      std::cout << "2. Ask for help\n";
   }

   // If we are asking for help
   if (option == "2")
   {
      std::pair<bool, std::string> cardAndHelp{ true, "" };
      return cardAndHelp;
   }

   // Ask human for card
   std::cout << "Which card will you discard: \n";
   std::string nameOfCard;
   std::cin >> nameOfCard;

   nameOfCard = cardInputToUppercase(nameOfCard);

   std::pair<bool, std::string> cardAndHelp{ false, nameOfCard };
   return cardAndHelp;
}


/* *********************************************************************
Function Name: toString()
Purpose: Return a string representation of the player type
Parameters:
         none
Return Value: a string, containing "Human"
Local Variables:
         none
Algorithm:
         1) Return "Human"
Assistance Received: none
********************************************************************* */
std::string Human::toString() const
{
   return "Human";
}


/* *********************************************************************
Function Name: printMoveOption()
Purpose: Return a string representation of the player type
Parameters:
         none
Return Value: none
Local Variables:
         none
Algorithm:
         1) Print the move options
            1. Draw from draw pile
            2. Draw form discard pile
Assistance Received: none
********************************************************************* */
void Human::printMoveOption()
{
   std::cout <<
      "1. Draw from draw pile\n" <<
      "2. Draw from discard pile\n";
}

/* *********************************************************************
Function Name: cardInputToUppercase()
Purpose: Returns a copy of card the user entered but in all capital letters
Parameters:
         string card, the card to capitalize
Return Value: none
Local Variables:
         none
Algorithm:
         1) Loop through each character of card passed in
         2) Capitalize each character
         3) Return the card
Assistance Received: none
********************************************************************* */
std::string Human::cardInputToUppercase(std::string card)
{
   // Loop through each index of string and convert to capital equivalent.
   for (size_t i = 0; i < card.length(); i++)
   {
      card[i] = toupper(card[i]);
   }

   return card;
}