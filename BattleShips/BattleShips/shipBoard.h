#pragma once
#include "Ship.h"
#include"BoardCoord.h"

enum guessResult
{
	hit,
	miss,
	previouslyGuessed,
	destroyed,
	lastBoatDestroyed
};

class ShipBoard
{
public:
	const int arrsize = 10;
	char Boardarr[10][10];// 10 X 10 grid
	bool PlayerWins = false;// checks if the player has won.
	int shipCounter = 5;// counter to see how many ships are left on the board

	/*
	 the ships.
	*/
	Ship* carrier; 
	Ship* battleship;
	Ship* cruiser;
	Ship* submarine;
	Ship* destroyer;
	
	ShipBoard(bool isAutoSetup);//default constructer

	
	void blankBoard();//creates a blank array board
	
	void setupShip(Ship* currentShip, bool isAutoSetup);//process of placing the ships on the board.
	
	bool positionShip(Ship* shipType, Ship* currentSetupShip);// checks if the ship is in a valid place before placing the ship.
	
	void printBoard();// display the board with ships
	
	void printHiddenBoard();// display the board without ships

	bool Playerchoice();// player chooses where they wish to shoot at

	guessResult Guess(BoardCoord currentCoord);// returns the result of the AI or Players guess. 

	guessResult shipIcon(BoardCoord currentCoord);// process of checking the status of the ship.
};

