#include "AI.h"


AI::AI(ShipBoard* Player)//defualt Constructer
{

}

void AI::Randomise(BoardCoord* coord)//this randomizes a corrdinate for the AI
{
	coord->xCoord = (rand() % 9) + 0;
	coord->yCoord = (rand() % 9) + 0;
}

bool AI::findNexGuess(ShipBoard* Player) // generates a valid guess
{
	/*
	 this function will either pick a random location from the board (randomHunt).

	 Or if the AI hit a ship last go, then the AI chooses a place either left, right , up or down from the previous shot.
	*/
		if (randomHunt == true)
		{
			Randomise(&randomBC);//random coord
			result = Player->Guess(randomBC);// finds the result of what the AI chose
			if (result == hit)
			{
				startPos = randomBC;// makes this shot the starting position to go back to if the next shot misses or goes off the grid.
				lastPos = randomBC;// last position is the previous shot.
				randomHunt = false; // the AI is no longer picking random places.
				return false; // goes to players turn.
			}
			else if (result == miss)
			{
				return false; // players turn.
			}
			else if(result == previouslyGuessed)
			{
				return true; // goes again to pick a place it has not shot at yet.
			}
			
		}
		else // decision for the direction from previous hit
		{
			if (SearchDirection == left)
			{
				if (nextPosition(lastPos, SearchDirection) == false) {// this will check if the next guess is off the grid.
					// if the next guess is off the grid
					lastPos = startPos;// set the previous shot back to the very first hit on the ship.
					SearchDirection = nextSearchDirection(SearchDirection);// change direction of ship search
					return true;// continues search.
				}
				else// if next guess is on the grid.
				{
					lastPos.xCoord--;// last position + 1;
				}
			}
			else if (SearchDirection == right)
			{
				if (nextPosition(lastPos, SearchDirection) == false) {
					lastPos = startPos;
					SearchDirection = nextSearchDirection(SearchDirection);
					return true;
				}
				else
				{
					lastPos.xCoord++;
					
				}
			}
			else if (SearchDirection == up)
			{
				if (nextPosition(lastPos, SearchDirection) == false) {
					lastPos = startPos;
					SearchDirection = nextSearchDirection(SearchDirection);
					return true;
				}
				else 
				{
					lastPos.yCoord--;
					
				}
			}
			else if (SearchDirection == down)
			{
				if (nextPosition(lastPos, SearchDirection) == false) {
					lastPos = startPos;
					SearchDirection = nextSearchDirection(SearchDirection);
					return true;
				}
				else
				{
					lastPos.yCoord++;
				}
			}
			guessResult AIResult;
			AIResult = Player->Guess(lastPos); // checks the result of the guess
			if (AIResult == previouslyGuessed)
			{
				SearchDirection = nextSearchDirection(SearchDirection);// changes the direction of search
				
				return true;// AI continues to search

			}
			if (AIResult == hit) 
			{
				return false;//players turn
			}
			if(AIResult == miss)
			{
				lastPos = startPos;// set back to first hit of ship
				SearchDirection = nextSearchDirection(SearchDirection);// change direction of search
				return false;// player turn
			}
			if (AIResult == destroyed)
			{
				lastPos = startPos;
				randomHunt = true; // now that the ship is destroyed, the AI goes back to choosing random places
				SearchDirection = left; // direction defualts to left
				return false;// players turn
			}
			if (AIResult == lastBoatDestroyed)
			{
				AIvictory = true;// AI wins
				return false;// ends turn.
			}

			
		}
	
}

bool AI::nextPosition(BoardCoord currentCoord, eDirection currentDir) 
{
	/*
	this is a check to see if the AI has searched beyond the grid.

	if it has then the direction of search changes and position is reset to the first hit.
	*/
	if (currentCoord.xCoord >= 1 && currentDir == eDirection::left) 
	{
		return true;
	}
	else if (currentCoord.xCoord <= 8 && currentDir == eDirection::right) 
	{
		return true;
	}
	else if (currentCoord.yCoord >= 1 && currentDir == eDirection::up) 
	{
		return true;
	}
	else if (currentCoord.yCoord <= 8 && currentDir == eDirection::down) 
	{
		return true;
	}
	else 
	{
		return false;// search is beyond the grid
	}
}

eDirection AI::nextSearchDirection(eDirection  currentDirection){
	eDirection returnValue = left;
	
	// this simply changes the direction of search.
	switch (currentDirection) {
	case left:
		returnValue = right;
		break;
	case right:
		returnValue = up;
		break;
	case up:
		returnValue = down;
		break;
	case down:
		returnValue = left;
		break;
	}
	return returnValue;
}



