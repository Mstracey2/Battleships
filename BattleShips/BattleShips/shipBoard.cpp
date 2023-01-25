#include "shipBoard.h"
#include<windows.h>
#include <iostream>

ShipBoard::ShipBoard( bool isAutoSetup) 
{ 
    blankBoard();// creates an empty board
    /* 
        Ship objects
        
        each one has its own icon, length and hit count
    */
    carrier = new Ship(1, 1, 5, 'C', 5);
    battleship = new Ship(NULL, NULL, 4, 'B', 4);// coordinates are set to null so they dont show on the board straight away
    cruiser = new Ship(NULL, NULL, 3, 'c', 3);
    submarine = new Ship(NULL, NULL, 3, 'S', 3);
    destroyer = new Ship(NULL, NULL, 2, 'D', 2);

    /* Player goes through the process of placing each ship */
    setupShip(carrier, isAutoSetup);
    setupShip(battleship, isAutoSetup);
    setupShip(cruiser, isAutoSetup);
    setupShip(submarine, isAutoSetup);
    setupShip(destroyer, isAutoSetup);

    

}


void ShipBoard::blankBoard() 
{
    //Populate chart with empty spaces
    for (int i = 0; i < arrsize; i++)
    {
        for (int j = 0; j < arrsize; j++)
        {
            Boardarr[i][j] = '-';
        }
    }
}

bool ShipBoard::positionShip(Ship* shipType, Ship* currentSetupShip) 
{
    bool iconCheck;// checks if the place of shot was a ship icon
    bool settingUp = false;// switch for if the ship type being compared to the current ship is the same ship.(there is no need to check for collision as its the ship being placed)
    if (shipType == currentSetupShip) {
        settingUp = true;
    }

    if (shipType->shipCoord.xCoord != NULL)// will only check for collision is the ship is placed on the board
    {
        if (shipType->rotation == true)
        {
            if (settingUp)
            {
                for (int i = 0; i < shipType->length; i++)// loops until all ship icons are checked
                {
                    
                    if (Boardarr[shipType->shipCoord.yCoord - 1 + i][shipType->shipCoord.xCoord - 1] != '-' || Boardarr[shipType->shipCoord.yCoord - 1][shipType->shipCoord.xCoord - 1] != '-')
                    {
                        return false;// invalid position (goes back to original position)
                    }

                }
            }


            for (int i = 0; i < shipType->length; i++)// loops until all ship icons are placed
            {
                Boardarr[shipType->shipCoord.yCoord - 1 + i][shipType->shipCoord.xCoord - 1] = shipType->icon;
            }
        }

        else if (shipType->rotation == false)//same code as above but if the ship is in a different rotation
        {
            if (settingUp)
            {
                for (int i = 0; i < shipType->length; i++)
                {
                    if (Boardarr[shipType->shipCoord.yCoord - 1][shipType->shipCoord.xCoord - 1 + i] != '-' || Boardarr[shipType->shipCoord.yCoord - 1][shipType->shipCoord.xCoord - 1] != '-')
                    {
                        return false;
                    }
                }
            }

            for (int i = 0; i < shipType->length; i++)
            {
                Boardarr[shipType->shipCoord.yCoord - 1][shipType->shipCoord.xCoord - 1 + i] = shipType->icon;
            }

        }
    }
    return true;
}

void ShipBoard::printBoard() 
{
    int columnCount = 0;// column numbers display
    int rowCount = 0;// row numbers display
    for (int i = 0; i < arrsize; i++)// loops until the board is printed fully on the y axis.
    {
            
        if (i == 0) // prints the column numbers
        {
            std::cout << "  ";
            while (columnCount <= 9) 
            {
                std::cout << columnCount << " ";
                columnCount++;
            }
            std::cout << "\n";
        }
        std::cout << rowCount << " ";//prints the row numbers
        rowCount++;
        for (int j = 0; j < arrsize; j++)// loops until the board is printed fully on the x axis.
        {
            std::cout << Boardarr[i][j] << " ";// prints the Icon that matches the board arrays x and y corrdinate
        }
        std::cout << "\n";
    }
}

void ShipBoard::printHiddenBoard()
{
    /* This is the same as the print board function but it will hide the ships so the player cant see them */

    int columnCount = 0;
    int rowCount = 0;
    for (int i = 0; i < arrsize; i++)
    {

        if (i == 0)
        {
            std::cout << "  ";
            while (columnCount <= 9)
            {
                std::cout << columnCount << " ";
                columnCount++;
            }
            std::cout << "\n";
        }
        std::cout << rowCount << " ";
        rowCount++;
        for (int j = 0; j < arrsize; j++)
        {
            if (Boardarr[i][j] == carrier->icon || Boardarr[i][j] == cruiser->icon || Boardarr[i][j] == submarine->icon || Boardarr[i][j] == destroyer->icon || Boardarr[i][j] == battleship->icon)
            {
                //if the Icon in the array is equal to any ship icons
                std::cout << "-" << " ";// hides the ship icon
            }
            else
            {
                std::cout << Boardarr[i][j] << " ";// prints the icon.
            }

        }
        std::cout << "\n";
    }
}

void ShipBoard::setupShip(Ship* currentShip, bool isAutoSetup)
{
    //moves current ship to valid position

    currentShip->shipCoord.xCoord = 1;//sets the starting position for placing the ship (not NULL)
    currentShip->shipCoord.yCoord = 1;
    currentShip->oldxCoord = 1;//original position
    currentShip->oldyCoord = 1;
    
    bool finish = false;
    bool shipPlacementComplete = false;
    while (shipPlacementComplete == false)
    {
      
        
        blankBoard();// blanks board
        if (isAutoSetup)
        {
            currentShip->randomPosition();// randomizes the position of the ship if its the AI's ships.
        }
        if (finish)
        {
            shipPlacementComplete = true;// player has finished placing ships
        }

        if (positionShip(carrier, currentShip) == false) {// return false if ship position is overlapping 
                currentShip->lastPosition(isAutoSetup);// sets the position of the ship back to previous position(Player)/rerandomizes the position of ship(AI)
                positionShip(carrier, currentShip);// places ship again
                shipPlacementComplete = false;
        }
        if (positionShip(battleship, currentShip) == false) {

                currentShip->lastPosition(isAutoSetup);
                positionShip(battleship, currentShip);
                shipPlacementComplete = false;
        }
        if (positionShip(cruiser, currentShip) == false) {

                currentShip->lastPosition(isAutoSetup);
                positionShip(cruiser, currentShip);
                shipPlacementComplete = false;
        }
        if (positionShip(submarine, currentShip) == false) {

                currentShip->lastPosition(isAutoSetup);
                positionShip(submarine, currentShip);
                shipPlacementComplete = false;
        }
        if (positionShip(destroyer, currentShip) == false) {

                currentShip->lastPosition(isAutoSetup);
                positionShip(destroyer, currentShip);
                shipPlacementComplete = false;
            
        }

        if (isAutoSetup == false) // only does this for player as its not needed for AI placement
        {
            
            printBoard();//Print the chart
            cout << "\nWASD: move ship\n\n";//instructions
            cout << "R: rotate ship\n\n";
            cout << "SPACEBAR: place ship\n\n";
        }

        if (isAutoSetup)
        {
            finish = true;
        }
        else
        {
            shipPlacementComplete = currentShip->move();//player moves ship
        }

        
        system("CLS");
    }

    
}

bool ShipBoard::Playerchoice()
{
    BoardCoord choice;// players choice of coordinate shot
    bool Choicex = true;
    bool Choicey = false;
  while (Choicex == true)
  {
     std::cout << "select X coordinate:";

     std::cin >> choice.xCoord;



     if (choice.xCoord >= 0 && choice.xCoord <= 9)//if a valid spot on the grid
     {
                Choicey = true;
                Choicex = false;
     }
     else
     {
                std::cout << "\nyour coordinate is outside the grid, please try again!\n";
                Sleep(3000);    
     }

  }

  while (Choicey == true)
  {
    std::cout << "select Y coordinate:";

    std::cin >> choice.yCoord;

    if (choice.yCoord >= 0 && choice.yCoord <= 10)//if a valid spot on the grid
    {
     Choicey = false;
    }
    else
    {
        std::cout << "your coordinate is outside the grid, please try again!\n";
        Sleep(3000);
    }

  }

  guessResult pResult = Guess(choice);// gets result of players guess
  if (pResult == lastBoatDestroyed) 
  {
      PlayerWins = true;
      return false;
  }
  else if (pResult == destroyed) 
  {
      cout << "\nYOU DESTROYED A SHIP";
      Sleep(4000);
  }
  else if (pResult != previouslyGuessed)
  {
      return false;//end of players turn
  }
  else
  {
      return true;// player chooses again as the placement of shot was already chosen on a previous shot
  }

}

guessResult ShipBoard::Guess(BoardCoord currentCoord) 
{
    guessResult returnVal;

    guessResult iconCheck = shipIcon(currentCoord);// checks if the icon is a ship icon
    if (iconCheck == hit || iconCheck == destroyed)
    {
        Boardarr[currentCoord.yCoord][currentCoord.xCoord] = 'X';// changes the icon to a hit symbol
        returnVal = iconCheck;
        return returnVal;// returns hit or destroyed
    }
    else if (iconCheck == lastBoatDestroyed) 
    {
        return iconCheck;
    }
    else if (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == '-')// if a blank space
    {
        Boardarr[currentCoord.yCoord][currentCoord.xCoord] = 'O';// prints a miss symbol
        returnVal = miss;
        return returnVal;
    }
    else if((Boardarr[currentCoord.yCoord][currentCoord.xCoord] == 'X') || (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == 'O'))// checks for a previous choson coordinate
    {
        returnVal = previouslyGuessed;
        return returnVal;
    }
    else
    {
        returnVal = miss;
        return returnVal;
    }
}

guessResult ShipBoard::shipIcon(BoardCoord currentCoord)
{
    bool shipDestroyed = false;
     
    if (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == carrier->icon)
    {
        carrier->hitCount--;
        if (carrier->hitCount == 0) 
        {
            shipDestroyed = true;
            shipCounter--;// the amount of ships on the board - 1
        }
        else
        {
            return hit;
        }
        
    }
    else if (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == battleship->icon)
    {
        battleship->hitCount--;
        if (battleship->hitCount == 0)
        {
            shipDestroyed = true;
            shipCounter--;
        }
        else
        {
            return hit;
        }
    }
    else if (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == cruiser->icon)
    {
        cruiser->hitCount--;
        if (cruiser->hitCount == 0)
        {
            shipDestroyed = true;
            shipCounter--;
        }
        else
        {
            return hit;
        }
    }
    else if (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == submarine->icon)
    {
        submarine->hitCount--;
        if (submarine->hitCount == 0)
        {
            shipDestroyed = true;
            shipCounter--;
        }
        else
        {
            return hit;
        }
    }
    else if (Boardarr[currentCoord.yCoord][currentCoord.xCoord] == destroyer->icon)
    {
        destroyer->hitCount--;
        if (destroyer->hitCount == 0)
        {
            shipDestroyed = true;
            shipCounter--;
        }
        else
        {
            return hit;
        }
    }
    else 
    {
        return miss;
    }

    if (shipCounter == 0)// if all ships are destroyed, all boats are destroyed
    {
        return lastBoatDestroyed;
    }
    else if (shipDestroyed == true)
    {
        return destroyed;
    }
}

