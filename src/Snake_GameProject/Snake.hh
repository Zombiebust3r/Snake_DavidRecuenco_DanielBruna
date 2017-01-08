#pragma once
#include <list>
#include <iostream>
#include "InputManager.hh"
#include "Sprite.hh"

//Width and height of every cell
#define CELL 14

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

class Direction {
public:
	Direction();
	~Direction();
	Direction(Directions p_dir);
	Directions dir;

};

Direction::Direction() {}
Direction::~Direction() {}
Direction::Direction(Directions p_dir) : dir(p_dir) {}

class Coord {
public:
	Coord();
	~Coord();
	Coord(int p_x, int p_y);
	int x, y;
};
Coord::Coord() {}
Coord::~Coord() {}

Coord::Coord(int p_x, int p_y) : x(p_x), y(p_y) {}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Snake {
private:
	int gridCols, gridRows;

public:
	list<Coord> coordsRegister;
	list<Direction> dirRegister;

	int v;

	Snake();
	~Snake();
	Snake(Coord inicialPos, int p_v);

	//Inserts next coord in the "head" of the list.
	void IncreaseSize();

	//Returns the coords value of the head position in the list as a Coord variable. This is used to check colisions since the other parts of the snake just follow the head's path and should never collision with something the head didn't.
	Coord GetHeadCoord();

	//Compares two coords, either x or y, to know if they are EQUAL/HIGH/SMALL
	//bool CompareCoordsXY(int coord1, int coord2, comparisons desiredOperation);

	bool CheckPosition(Coord p_fruitCoord);

	void GiveGridLimits(int p_cols, int p_rows);

	bool CollisionsWallSnake();

	//This functions recieves the INPUT KEY that is being pressed from the INPUT MANAGER in order to know what is gonna be the direction the snake should go.
	Directions GetNewDir();

	void moveDir();

	//Move the coords inside the list. This list is gonna be used to draw and check colisions with objects.
	void moveSnake();

	//Draws the snake parts. Depending on the position of each part compared to the one before and next.
	void drawSnake();

private:
	Sprite snakeImg;
};
Snake::Snake() {
	coordsRegister.push_back({ 4, 1 });
	coordsRegister.push_back({ 3, 1 });
	coordsRegister.push_back({ 2, 1 });
	dirRegister.push_back(DIR_RIGHT);
	dirRegister.push_back(DIR_RIGHT);
	dirRegister.push_back(DIR_RIGHT);
	v = 1;
}
Snake::~Snake() {}

Snake::Snake(Coord inicialPos, int p_v) : v(p_v) {
	coordsRegister.push_back(inicialPos);
	coordsRegister.push_back({ inicialPos.x - 1, inicialPos.y });
	coordsRegister.push_back({ inicialPos.x - 2, inicialPos.y });
	dirRegister.push_back(DIR_RIGHT);
	dirRegister.push_back(DIR_RIGHT);
	dirRegister.push_back(DIR_RIGHT);
}

void Snake::IncreaseSize() {
	Coord headCoord;
	headCoord = GetHeadCoord();
	Directions headDir;
	headDir = dirRegister.begin()->dir;

	switch (headDir)
	{
	case DIR_UP:
		headCoord.y -= v;
		break;
	case DIR_DOWN:
		headCoord.y += v;
		break;
	case DIR_RIGHT:
		headCoord.x += v;
		break;
	case DIR_LEFT:
		headCoord.x -= v;
		break;
	default:
		break;
	}

	coordsRegister.push_front(headCoord);
	dirRegister.push_front(headDir);
}

bool Snake::CheckPosition(Coord p_fruitCoord) {
	for (auto it = coordsRegister.begin(); it != coordsRegister.end(); it++) {
		if (p_fruitCoord.x == it->x && p_fruitCoord.y == it->y) return true;
	}
	return false;

}

void Snake::GiveGridLimits(int p_cols, int p_rows) {
	gridCols = p_cols;
	gridRows = p_rows;

}

bool Snake::CollisionsWallSnake() {
	//auto it = coordsRegister.end();
	auto headIt = coordsRegister.begin();
	if (headIt->x == 0 || headIt->x == gridCols || headIt->y == 0 || headIt->y == gridRows) {	//
		return true;
	}
	else {
		for (auto it = coordsRegister.end();; it != coordsRegister.begin()) {
			it--;
			if (headIt->x == it->x && headIt->y == it->y) {	//
				return true;
			}
		}
		return false;
	}

}

////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Directions Snake::GetNewDir() {
	//Get new coord depending on the key the user is pressing --> use INPUT MANAGER
	Directions newDirection = DIR_UP;

	switch (IM.actualDir) {
	case DIR_UP: newDirection = DIR_UP; break;
	case DIR_RIGHT: newDirection = DIR_RIGHT; break;
	case DIR_LEFT: newDirection = DIR_LEFT; break;
	case DIR_DOWN: newDirection = DIR_DOWN; break;
	}

	return newDirection;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//Returns the coords of the head of the snake.
Coord Snake::GetHeadCoord() {
	Coord tmp;
	tmp.x = coordsRegister.begin()->x;
	tmp.y = coordsRegister.begin()->y;
	return tmp;
}


/*bool Snake::CompareCoordsXY(int coord1, int coord2, comparisons desiredOperation) {
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
}*/

/*
static int Snake::CheckPosition(int f_x, int f_y) {
for (auto it = coordsRegister.begin(); it != coordsRegister.end(); it++) {
if (f_x == it->x) return true;
if (f_y == it->y) return true;
}
return false;
}
*/

void Snake::moveDir() {
	auto itSecond = dirRegister.end();
	itSecond--;
	auto it = itSecond;

	for (it; it != dirRegister.begin(); it--) {
		itSecond--;
		it->dir = itSecond->dir;
	}

	Directions tmp = GetNewDir();
	itSecond->dir = tmp;

	/*
	auto itSecond = coordsRegister.end();
	itSecond--;
	auto it = itSecond;

	for (it; it != coordsRegister.begin(); it--) {			//In this loop we are gonna make a cascade effect with the coords. This simulates a snake-like movement.
	itSecond--;																		//This itereator is gonna be using to get the value of the one before the "it" is pointing.
	it->x = itSecond->x;															//			1						1 <-- itSecond			1 <-- itSecond								newCoord
	it->y = itSecond->y;															//			2 <-- itSecond   ==>	2 <-- it		==>		1 <-- it		==> outside the for:			1
	}																					//			3 <-- it				2						2												2

	//Put new coord depending on the direction the player is going, this new coord is given by the function GetNewCoord().
	Coord tmp = GetNewCoord();
	itSecond->x = tmp.x;
	itSecond->y = tmp.y;
	*/
}

void Snake::moveSnake() {
	moveDir();
	auto itSecond = dirRegister.end();
	itSecond--;
	auto it = coordsRegister.end();
	it--;

	for (it; it != coordsRegister.begin(); it--) {
		switch (itSecond->dir)
		{
		case DIR_UP:
			it->y -= v;
			break;
		case DIR_DOWN:
			it->y += v;
			break;
		case DIR_RIGHT:
			it->x += v;
			break;
		case DIR_LEFT:
			it->x -= v;
			break;
		default:
			break;
		}

		itSecond--;
	}

	//This is for the head of the snake since its not included inside the for. "it" and "itSecond" are pointing to the head of the snake.
	switch (itSecond->dir)
	{
	case DIR_UP:
		it->y -= v;
		break;
	case DIR_DOWN:
		it->y += v;
		break;
	case DIR_RIGHT:
		it->x += v;
		break;
	case DIR_LEFT:
		it->x -= v;
		break;
	default:
		break;
	}

	//Put new coord depending on the direction the player is going, this new coord is given by the function GetNewCoord().
	//Coord tmp = GetNewCoord();
	//itSecond->x = tmp.x;
	//itSecond->y = tmp.y;
}

void Snake::drawSnake() {
	//Need 3 iterators: Prev Now Next.	(The snake starts with 3 parts)
	list<Coord>::iterator prev, now, next, tail;
	prev = coordsRegister.begin();					//First position of the list
	next = coordsRegister.begin();	next++;			//Third position of the list	(will increase at the start of the for. This way it doesn't point to something that doesn't exist at the end of the for loop. It would have tried to point to the one after the tail taht obviously doesn't exist.)
	now = next;										//Second position of the list

	tail = coordsRegister.end();					//Tail position to make the for stop at that point
	tail--;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Draw head depending on what key the user is pressing. W: Upwards | A: Left | D: Rigt | S: Downwards
	switch (Directions headDir = dirRegister.begin()->dir) {
	case DIR_UP:
		snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_UP };
		snakeImg.Draw();
		break;
	case DIR_RIGHT:
		snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_RIGHT };
		snakeImg.Draw();
		break;
	case DIR_LEFT:
		snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_LEFT };
		snakeImg.Draw();
		break;
	case DIR_DOWN:
		snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_DOWN };
		snakeImg.Draw();
		break;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ToDo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Draws all the parts between the head and the tail.
	for (now; now != tail; now++) {
		next++;
																								//DIAGONAL MOVEMENT
		if (now->x == prev->x) {																//VERTICAL MOVEMENT
			if (now->x == next->x) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_BODY_VERT }; snakeImg.Draw();
			}
			else if (prev->x < next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_4 }; snakeImg.Draw(); }
			else if (prev->x > next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_3 }; snakeImg.Draw(); }
			else if (prev->x < next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_2 }; snakeImg.Draw(); }
			else if (prev->x > next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_1 }; snakeImg.Draw(); }
		}
		else if (now->y == prev->y) {															//HORIZONTAL MOVEMENT
			if (now->y == next->y) { snakeImg = { {}, ObjectID::SNAKE_BODY_HOR }; snakeImg.Draw();
			}
			else if (prev->x < next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_4 }; snakeImg.Draw(); }
			else if (prev->x > next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_3 }; snakeImg.Draw(); }
			else if (prev->x < next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_2 }; snakeImg.Draw(); }
			else if (prev->x > next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_1 }; snakeImg.Draw(); }
		}
		prev++;
	}

	//Draws the tail depending on the previous part of the snake. At this point now should be pointing to the last position(tail) and prev should be pointing the one before.
	if (now->x == prev->x) {																	//VERTICAL MOVEMENT
		if (now->y < prev->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_DOWN }; snakeImg.Draw(); }	//Downwards
		if (now->y > prev->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_UP }; snakeImg.Draw();	}	//Upwards
	}
	else {																						//HORIZONTAL MOVEMENT
		if (now->x < prev->x) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_RIGHT }; snakeImg.Draw();}	//Right
		if (now->x > prev->x) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_LEFT }; snakeImg.Draw(); }	//Left
	}
}