#pragma once
#include<string>
#include"BoardCoord.h"
using namespace std;


	class Ship
	{
	public:
		char icon;// Icon of the ship
		int shipEnd;// the end of the ship
		int hitCount;// count for how many times its hit
		BoardCoord shipCoord;// coordinate of the first ship Icon
		int length;// length of the ship
		bool controlC = false;// switch for moving ship
		int overGrid = 0;// corrector for when the player tries to move a ship beyond the grid
		bool rotation = false;// horizontal
		int oldxCoord = 0;
		int oldyCoord = 0;
		bool oldRotation = false;
		char control = ' ';// player input

		Ship(int xCoord, int yCoord, int length, char icon, int hitCount);// constructer
		
		bool move();// process of moving the ship (Player)
		
		bool randomPosition();// process of randomizing ship placement (AI)
		
		void lastPosition(bool isAutosetup);// function that returns ship to previous location if movement was invalid.
	};



