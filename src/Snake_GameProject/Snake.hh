#pragma once
#include <list>
#include <iostream>
#include "InputManager.hh"

								//==========================================================================
								//==					  How should this be used						  ==
								//==																	  ==
								//==		First you move the snake after drawing the map then			  ==
								//==		draw the apples. After drawing check for colisions.			  ==
								//==		If the snake colisions with a wall GAMEOVER, if it			  ==
								//==		collisions with an apple give it points and increase		  ==
								//==		its size with the given funtion in the snake class.			  ==
								//==																	  ==
								//==																	  ==
								//==========================================================================

using namespace std;

enum comparisons
{
	EQUAL, DIFF, SMALLER, HIGHER
};

class Coord {
public:
	Coord();
	~Coord();
	Coord(int p_x, int p_y);
	int x, y;
	
};

Coord::Coord(int p_x, int p_y) : x(p_x), y(p_y) {}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Snake
{
private:
	list<Coord> coordsRegister;

public:
	Snake();
	~Snake();
	Snake(Coord inicialPos);

	//Inserts next coord in the "head" of the list.
	void IncreaseSize(Coord p_coord);

	//Returns the coords value of the head position in the list as a Coord variable. This is used to check colisions since the other parts of the snake just follow the head's path and should never collision with something the head didn't.
	Coord GetHeadCoord();

	//Compares two coords, either x or y, to know if they are EQUAL/HIGH/SMALL
	bool CompareCoordsXY(int coord1, int coord2, comparisons desiredOperation);

	//This functions recieves the INPUT KEY that is being pressed from the INPUT MANAGER in order to know what is gonna be the direction the snake should go.
	Coord GetNewCoord();

	//Move the coords inside the list. This list is gonna be used to draw and check colisions with objects.
	void moveSnake();

	//Draws the snake parts. Depending on the position of each part compared to the one before and next.
	void drawSnake();
};

Snake::Snake(Coord inicialPos) {
	coordsRegister.push_back(inicialPos);
	coordsRegister.push_back(inicialPos);
	coordsRegister.push_back(inicialPos);
}

void Snake::IncreaseSize(Coord p_coord) {
	coordsRegister.push_front(p_coord);
	list <Coord>::iterator iCoords;
	iCoords->x = 1;
}


////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Coord Snake::GetNewCoord() {
	//Get new coord depending on the key the user is pressing --> use INPUT MANAGER
	Coord tmp;

	switch (IM.actualDir) {
		case DIR_UP: tmp.y--; break;
		case DIR_RIGHT: tmp.x++; break;
		case DIR_LEFT: tmp.x--; break;
		case DIR_DOWN: tmp.y++; break;
	}

	coordsRegister.begin()->x = tmp.x;
	coordsRegister.begin()->y = tmp.y;
	return tmp;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//Returns the coords of the head of the snake.
Coord Snake::GetHeadCoord() {
	Coord tmp;
	tmp.x = coordsRegister.begin()->x;
	tmp.y = coordsRegister.begin()->y;
}


bool Snake::CompareCoordsXY(int coord1, int coord2, comparisons desiredOperation) {
	switch (desiredOperation)
	{
	case EQUAL:
		return coord1 == coord2;
		break;
	case DIFF:
		return coord1 != coord2;
		break;
	case SMALLER:
		return coord1 < coord2;
		break;
	case HIGHER:
		return coord1 > coord2;
		break;
	default:
		break;
	}
}


void Snake::moveSnake() {
	auto itSecond = coordsRegister.end();
	itSecond--;																			//This itereator is gonna be using to get the value of the one before the it is pointing.

	for (auto it = coordsRegister.end(); it != coordsRegister.begin(); it--) {			//In this loop we are gonna make a cascade effect with the coords. This simulates a snake-like movement.
		it->x = itSecond->x;															//			1						1 <-- itSecond			1 <-- itSecond								newCoord
		it->y = itSecond->y;															//			2 <-- itSecond   ==>	2 <-- it		==>		1 <-- it		==> outside the for:			1
																						//			3 <-- it				2						2												2
																						//
		itSecond--;
	}

	//Put new coord depending on the direction the player is going, this new coord is given by the function GetNewCoord().
	Coord tmp = GetNewCoord();
	itSecond->x = tmp.x;
	itSecond->y = tmp.y;
}

void Snake::drawSnake() {
	//Need 3 iterators: Prev Now Next.	(The snake starts with 3 parts)
	list<Coord>::iterator prev, now, next;
	prev = coordsRegister.begin();					//First position of the list
	next = coordsRegister.begin();	next++;			//Third position of the list	(will increase at the start of the for. This way it doesn't point to something that doesn't exist at the end of the for loop. It would have tried to point to the one after the tail taht obviously doesn't exist.)
	now = next;										//Second position of the list
	
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Draw head depending on what key the user is pressing. W: Upwards | A: Left | D: Rigt | S: Downwards
	switch (IM.actualDir) {
	case DIR_UP:

		break;
	case DIR_RIGHT:

		break;
	case DIR_LEFT:

		break;
	case DIR_DOWN:

		break;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Draws all the parts between the head and the tail.
	for (now; now != coordsRegister.end(); now++) {
		
		//DIAGONAL MOVEMENT
		if (now->x == prev->x) {							//VERTICAL MOVEMENT
			if (now->x == next->x)								{ /*VERTICAL LINE*/ }
			else if (prev->x < next->x && prev->y > next->y)	{ /*Diagonal UPRIGHT	VERTICAL MOVEMENT*/ }
			else if (prev->x > next->x && prev->y > next->y)	{ /*Diagonal UPLEFT		VERTICAL MOVEMENT*/ }
			else if (prev->x < next->x && prev->y < next->y)	{ /*Diagonal DOWNRIGHT  VERTICAL MOVEMENT*/ }
			else if (prev->x > next->x && prev->y < next->y)	{ /*Diagonal DOWNLEFT	VERTICAL MOVEMENT*/ }
		}
		else if(now->y == prev->y){							//HORIZONTAL MOVEMENT
			if (now->y == next->y)								{ /*HORIZONTAL LINE*/ }
			else if (prev->x < next->x && prev->y > next->y)	{ /*Diagonal UPRIGHT		HORIZONTAL MOVEMENT*/ }
			else if (prev->x > next->x && prev->y > next->y)	{ /*Diagonal UPLEFT		HORIZONTAL MOVEMENT*/ }
			else if (prev->x < next->x && prev->y < next->y)	{ /*Diagonal DOWNRIGHT	    HORIZONTAL MOVEMENT*/ }
			else if (prev->x > next->x && prev->y < next->y)	{ /*Diagonal DOWNLEFT    	HORIZONTAL MOVEMENT*/ }
		}
	}

	//Draw the tail depending on the previous part of the snake. At this point now should be pointing to the last position(tail) and prev should be pointing the one before.
	if (now->x == prev->x) {													//VERTICAL MOVEMENT
		if (now->y < prev->y) { /* Draw tail in a DOWNWARDS direction */	}	//Downwards
		if (now->y > prev->y) { /* Draw tail in a UPWARDS direction */		}	//Upwards
	} 
	else  {																		//HORIZONTAL MOVEMENT
		if (now->x < prev->x) { /* Draw tail going RIGHT */					}	//Right
		if (now->x > prev->x) {	/* Draw tail going LEFT */					}	//Left
	}
}