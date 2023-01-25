// BattleShips.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Ship.h"
#include "shipBoard.h"
#include "AI.h"
#include<windows.h>
#include<time.h>

using namespace std;



int main()
{
    void playerWins(); // displays winner screen
    void AIWins();// displays Loser screen
    
    // setup bools
    const bool automaticSetup = true;
    const bool manualSetup = false;

    
    srand(time(NULL));//new random seed

    ShipBoard* computerBoard = new ShipBoard(automaticSetup);// AI's Board
    ShipBoard* playerBoard = new ShipBoard(manualSetup);// Player's board
    AI* AIop = new AI(playerBoard);//AI
   
    bool GameRun = true;
    
    while (GameRun == true) 
    {
        bool playerTurn = true;
        while (playerTurn == true)// player's turn
        {
            system("CLS");

            //prints the boards
            cout << "\n ------Opponent------\n";
            computerBoard->printHiddenBoard();
            cout << "\n --------You---------\n";
            playerBoard->printBoard();
            playerTurn = computerBoard->Playerchoice();//players choice
        }
        if (computerBoard->PlayerWins == true)
        {
            system("CLS");
            playerWins();//winner screen
            break;//game over
        }
        bool AITurn = true;
        while (AITurn == true)// AI turn
        {
            AITurn = AIop->findNexGuess(playerBoard); // loops until a valid guess
        }
        if (AIop->AIvictory == true)
        {
            system("CLS");
            AIWins();// loser screen
            cout << "\n ------Opponent------\n";
            computerBoard->printBoard();//shows the AI's board but not hidden.
            break;//game over
        }
        
        
        
    }
    
}

void playerWins() 
{
    cout << R"(__   __            _    _ _       _ 
\ \ / /           | |  | (_)     | |
 \ V /___  _   _  | |  | |_ _ __ | |
  \ // _ \| | | | | |/\| | | '_ \| |
  | | (_) | |_| | \  /\  / | | | |_|
  \_/\___/ \__,_|  \/  \/|_|_| |_(_)
                                    
                                    )";
}

void AIWins()
{
    cout << R"(__   __            _                    _ 
\ \ / /           | |                  | |
 \ V /___  _   _  | |     ___  ___  ___| |
  \ // _ \| | | | | |    / _ \/ __|/ _ \ |
  | | (_) | |_| | | |___| (_) \__ \  __/_|
  \_/\___/ \__,_| \_____/\___/|___/\___(_)
                                          
                                          )";
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
