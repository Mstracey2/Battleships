#include "Ship.h"
#include <string>
#include <iostream>
#include <conio.h>




    Ship::Ship (int xCoord, int yCoord, int length, char icon, int hitCount)//constructer
    {
        shipCoord.xCoord = xCoord;
        shipCoord.yCoord = yCoord;
		this->length = length;
		this->shipEnd = xCoord + length - 1;
        this->icon = icon;
        this->hitCount = hitCount;
	}

    void Ship::lastPosition(bool isAutoSetup) 
    {
        if (isAutoSetup) //changes position to another place (AI)
        {
            randomPosition();
        }
        else //returns to orignal position (Player)
        {
            shipCoord.xCoord = oldxCoord;
            shipCoord.yCoord = oldyCoord;
            rotation = oldRotation;
        }
            
    }

    bool Ship::move()//player moving ships
    {
        //original positions
        oldxCoord = shipCoord.xCoord;
        oldyCoord = shipCoord.yCoord;
        oldRotation = rotation;

        controlC = false;
        while (controlC == false)
        {
            wchar_t control;
            control = _getch();

            if (control == 'w')
            {
                shipCoord.yCoord--;//UP
                controlC = true;

                if (shipCoord.yCoord < 1)//returns if off grid
                {
                    shipCoord.yCoord++;
                }

            }

            else if (control == 's')
            {
                shipCoord.yCoord++;//DOWN
                controlC = true;

                if (shipCoord.yCoord > 10)//returns if off grid
                {
                    shipCoord.yCoord--;
                }

            }

            else if (control == 'd')
            {
                shipCoord.xCoord++;//RIGHT
                controlC = true;

                if (shipCoord.xCoord > 10)//returns if off grid
                {
                    shipCoord.xCoord--;
                }
            }

            else if (control == 'a')
            {

                shipCoord.xCoord--;//LEFT
                controlC = true;

                if (shipCoord.xCoord < 1)//returns if off grid
                {
                    shipCoord.xCoord++;
                }

            }

            else if (control == 'r')
            {
                if (rotation == false)
                {
                    rotation = true;//vertical

                }
                else
                {
                    rotation = false;//horizontal
                }

                controlC = true;
            }

            else if (control == ' ')//SPACEBAR
            {
                return true;// ship has been place
            }

            if (rotation == true)//vertical
            {
                shipEnd = shipCoord.yCoord + length - 1;// shipend is changed to y axis
                if (shipEnd > 10)// is the end of the ship is beyond grid
                {
                    overGrid = 10 - shipEnd;// overgrid is how far the ship is off
                    shipCoord.yCoord = shipCoord.yCoord + overGrid;// the ship is pushed back to a valid position
                }
            }
            else//horizontal
            {
                shipEnd = shipCoord.xCoord + length - 1;// shipend is changed to x axis
                if (shipEnd > 10)
                {
                    overGrid = 10 - shipEnd;
                    shipCoord.xCoord = shipCoord.xCoord + overGrid;
                }
            }

            return false;
        };
    } 

    bool Ship::randomPosition() //AI moving Ships
    {
        shipCoord.xCoord = oldxCoord;// orignal position
        shipCoord.yCoord = oldyCoord;
        oldRotation = rotation;

        int randomChoice = (rand() % 2) + 1;// random rotation
        if (randomChoice == 1) 
        {
            rotation = true;
        }
        else 
        {
            rotation = false;
        }

        if (rotation == true) //vertical, any column, clip row
        {
            shipCoord.xCoord = (rand() % 10) + 1;
            shipCoord.yCoord = (rand() % (10 -length + 1))  + 1;
            
            shipEnd = shipCoord.yCoord + length - 1;
            if (shipEnd > 10)
            {
                overGrid = 10 - shipEnd;
                shipCoord.yCoord = shipCoord.yCoord + overGrid;
            }
        }
        else//horizontal, any row, clip column 
        {
            shipCoord.yCoord = (rand() % 10) + 1;
            shipCoord.xCoord = (rand() % (10 - length + 1)) + 1;
            shipEnd = shipCoord.xCoord + length - 1;
            if (shipEnd > 10)
            {
                overGrid = 10 - shipEnd;
                shipCoord.xCoord = shipCoord.xCoord + overGrid;
            }
            
        }
        
        if ((shipCoord.xCoord != oldxCoord) && (shipCoord.yCoord != oldyCoord))
        {
            return true; //found empty space for ship
        }

    }