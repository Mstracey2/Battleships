#pragma once
#include"BoardCoord.h"
#include"shipBoard.h"
#include <list>

enum eDirection
{
	left,
	right,
	up,
	down
};

class AI
{
	
	public:
		bool AIvictory = false;// AI Win check
		BoardCoord startPos;// starting position of ship search
		BoardCoord lastPos;// previous position of ship search
		bool randomHunt = true;// switch for AI to go random placement mode
		BoardCoord randomBC;// random coordinate
		void Randomise(BoardCoord* coord);// coordinate randomizer
		eDirection SearchDirection = eDirection::left;// direction of search when searching for ship
		guessResult result = guessResult::miss;// result of placement choice
		 bool nextPosition(BoardCoord currentCoord, eDirection currentDir); // checker for next placement to see if it goes beyond the grid
		 bool findNexGuess(ShipBoard* Player); // Keeps searching until it makes a valid hit, miss etc (returns false);
		 eDirection nextSearchDirection(eDirection currentDirection);// next direction of search
		 
		 AI(ShipBoard* Player);// constructer
};
