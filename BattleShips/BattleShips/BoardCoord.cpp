#include "BoardCoord.h"
#include <iostream>


BoardCoord::BoardCoord()
{
	xCoord = -1;
	yCoord = -1;
}

BoardCoord::BoardCoord(int xCoord, int yCoord)//constructer
{
	this->xCoord = xCoord;
	this->yCoord = yCoord;
}

