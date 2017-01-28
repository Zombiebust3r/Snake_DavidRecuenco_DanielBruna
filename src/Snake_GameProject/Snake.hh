#pragma once
#include <list>
#include <iostream>
#include "SnakeGrid.hh"
#include "Score.hh"
#include "System.hh"
#include "Countdown.hh"


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

//! Identifies directional keys as 'W' and Up arrow for the Direction UP, etc.
enum Directions {
	DIR_UP,			// W & UP
	DIR_DOWN,		// S & DOWN
	DIR_RIGHT,		// D & RIGHT
	DIR_LEFT		// A & LEFT
};

namespace {
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
		Directions actualDirection;
		int v;

		Snake();
		~Snake();
		Snake(Coord inicialPos, int p_v);

		void GetKeys();

		//Inserts next coord in the "head" of the list.
		void IncreaseSize();

		//Returns the coords value of the head position in the list as a Coord variable. This is used to check colisions since the other parts of the snake just follow the head's path and should never collision with something the head didn't.
		Coord GetHeadCoord();

		//Compares two coords, either x or y, to know if they are EQUAL/HIGH/SMALL
		//bool CompareCoordsXY(int coord1, int coord2, comparisons desiredOperation);

		bool CheckPosition(Coord p_fruitCoord);

		void GiveGridLimits(Mode mode);

		void GiveGridLimits(int p_r, int p_c);

		void SetSnakeInicialPos(Mode mode);

		bool CollisionsWallSnake();

		//This functions recieves the INPUT KEY that is being pressed from the INPUT MANAGER in order to know what is gonna be the direction the snake should go.
		Directions GetNewDir();

		void moveDir();

		//Move the coords inside the list. This list is gonna be used to draw and check colisions with objects.
		void moveSnake();

		//Draws the snake parts. Depending on the position of each part compared to the one before and next.
		void drawSnake();

		void ResetSnakeOnDeath(Mode mode);

	private:
		Sprite snakeImg;
	};
	Snake::Snake() {
		coordsRegister.push_back({ 20, 10 });
		coordsRegister.push_back({ 19, 10 });
		coordsRegister.push_back({ 18, 10 });
		dirRegister.push_back(DIR_RIGHT);
		dirRegister.push_back(DIR_RIGHT);
		dirRegister.push_back(DIR_RIGHT);
		actualDirection = DIR_RIGHT;
		v = 1;
		gridCols = 15;
		gridRows = 8;
	}
	Snake::~Snake() {}

	Snake::Snake(Coord inicialPos, int p_v) : v(p_v) {
		coordsRegister.push_back(inicialPos);
		coordsRegister.push_back({ inicialPos.x - 1, inicialPos.y });
		coordsRegister.push_back({ inicialPos.x - 2, inicialPos.y });
		dirRegister.push_back(DIR_RIGHT);
		dirRegister.push_back(DIR_RIGHT);
		dirRegister.push_back(DIR_RIGHT);
		actualDirection = DIR_RIGHT;
		gridCols = 15;
		gridRows = 8;
	}

	void Snake::GetKeys() {
		if ((IM.IsKeyDown<SDLK_UP>() || IM.IsKeyDown<'w'>()) && actualDirection != DIR_DOWN) {
			actualDirection = DIR_UP;
		}
		else if ((IM.IsKeyDown<SDLK_LEFT>() || IM.IsKeyDown<'a'>()) && actualDirection != DIR_RIGHT) {
			actualDirection = DIR_LEFT;
		}
		else if ((IM.IsKeyDown<SDLK_DOWN>() || IM.IsKeyDown<'s'>()) && actualDirection != DIR_UP) {
			actualDirection = DIR_DOWN;
		}
		else if ((IM.IsKeyDown<SDLK_RIGHT>() || IM.IsKeyDown<'d'>()) && actualDirection != DIR_LEFT) {
			actualDirection = DIR_RIGHT;
		}
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

	void Snake::GiveGridLimits(Mode mode) {
		switch (mode) { //Cols = 15, Rows = 8
		case EASY: gridCols *= 5; gridRows *= 5; break;
		case MEDIUM: gridCols *= 2; gridRows *= 2; break;
		case HARD: gridCols *= 1; gridRows *= 1; break;
		}
	}

	void Snake::GiveGridLimits(int p_r, int p_c) {
		gridCols *= p_c; gridRows *= p_r;
	}

	void Snake::SetSnakeInicialPos(Mode mode) {
		actualDirection = DIR_RIGHT;
		auto it = coordsRegister.begin();
		switch(mode) {
		case EASY:		// CABEZA
			it->x = 26;
			it->y = 20;
			it++;		// CUERPO
			it->x = 25;
			it->y = 20;
			it++;		// COLA
			it->x = 24;
			it->y = 20;
			break;

		case MEDIUM:		// CABEZA
			it->x = 12;
			it->y = 8;
			it++;		// CUERPO
			it->x = 11;
			it->y = 8;
			it++;		// COLA
			it->x = 10;
			it->y = 8;
			break;

		case HARD:		// CABEZA
			it->x = 6;
			it->y = 4;
			it++;		// CUERPO
			it->x = 5;
			it->y = 4;
			it++;		// COLA
			it->x = 4;
			it->y = 4;
			break;
		}/*
		int tmpRows, tmpCols;
		tmpRows = gridRows / 2;
		tmpCols = gridCols / 2;
		for (auto it = coordsRegister.begin(); it != coordsRegister.end(); it++) {
			it->x = tmpCols--;
			it->y = tmpRows;
		}*/
	}

	bool Snake::CollisionsWallSnake() {
		//auto it = coordsRegister.end();
		auto headIt = coordsRegister.begin();
		if (headIt->x <= 1 || headIt->x >= gridCols || headIt->y <= 1 || headIt->y >= gridRows) {	//
			return true;
		}

		else {
			for (auto it = coordsRegister.end(); it != headIt;) {
				it--;
				if (headIt->x == it->x && headIt->y == it->y && headIt != it) {	//
					return true;
				}
			}
			return false;
		}

	}

	
	Directions Snake::GetNewDir() {
		//Get new coord depending on the key the user is pressing --> use INPUT MANAGER
		Directions newDirection = DIR_UP;

		switch (actualDirection) {
		case DIR_UP: newDirection = DIR_UP; break;
		case DIR_RIGHT: newDirection = DIR_RIGHT; break;
		case DIR_LEFT: newDirection = DIR_LEFT; break;
		case DIR_DOWN: newDirection = DIR_DOWN; break;
		}
		return newDirection;
	}


	//Returns the coords of the head of the snake.
	Coord Snake::GetHeadCoord() {
		Coord tmp;
		tmp.x = coordsRegister.begin()->x;
		tmp.y = coordsRegister.begin()->y;
		return tmp;
	}

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

		
		//Draw head depending on what key the user is pressing. W: Upwards | A: Left | D: Rigt | S: Downwards
		switch (Directions headDir = dirRegister.begin()->dir) {
		case DIR_UP:
			snakeImg = { { ((CELL / 2) + (prev->x*CELL)),((120 + (CELL / 2)) + (prev->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_UP };
			snakeImg.Draw();
			break;
		case DIR_RIGHT:
			snakeImg = { { ((CELL / 2) + (prev->x*CELL)),((120 + (CELL / 2)) + (prev->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_RIGHT };
			snakeImg.Draw();
			break;
		case DIR_LEFT:
			snakeImg = { { ((CELL / 2) + (prev->x*CELL)),((120 + (CELL / 2)) + (prev->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_LEFT };
			snakeImg.Draw();
			break;
		case DIR_DOWN:
			snakeImg = { { ((CELL / 2) + (prev->x*CELL)),((120 + (CELL / 2)) + (prev->y*CELL)), CELL, CELL }, ObjectID::SNAKE_HEAD_DOWN };
			snakeImg.Draw();
			break;
		}
		

		//Draws all the parts between the head and the tail.
		for (now; now != tail; now++) {
			next++;
			//DIAGONAL MOVEMENT
			if (now->x == prev->x) {																//VERTICAL MOVEMENT
				if (now->x == next->x) {
					snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_BODY_VERT }; snakeImg.Draw();
				}
				else if (prev->x < next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_4 }; snakeImg.Draw(); }
				else if (prev->x > next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_3 }; snakeImg.Draw(); }
				else if (prev->x < next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_2 }; snakeImg.Draw(); }
				else if (prev->x > next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_1 }; snakeImg.Draw(); }
			}
			else if (now->y == prev->y) {															//HORIZONTAL MOVEMENT
				if (now->y == next->y) {
					snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_BODY_HOR }; snakeImg.Draw();
				}
				else if (prev->x < next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_1 }; snakeImg.Draw(); }
				else if (prev->x > next->x && prev->y > next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_2 }; snakeImg.Draw(); }
				else if (prev->x < next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_3 }; snakeImg.Draw(); }
				else if (prev->x > next->x && prev->y < next->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_CURVE_4 }; snakeImg.Draw(); }
			}
			prev++;
		}

		//Draws the tail depending on the previous part of the snake. At this point now should be pointing to the last position(tail) and prev should be pointing the one before.
		if (now->x == prev->x) {																	//VERTICAL MOVEMENT
			if (now->y < prev->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_UP }; snakeImg.Draw(); }	//Downwards
			if (now->y > prev->y) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_DOWN }; snakeImg.Draw(); }	//Upwards
		}
		else {																						//HORIZONTAL MOVEMENT
			if (now->x < prev->x) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_LEFT }; snakeImg.Draw(); }	//Right
			if (now->x > prev->x) { snakeImg = { { ((CELL / 2) + (now->x*CELL)),((120 + (CELL / 2)) + (now->y*CELL)), CELL, CELL }, ObjectID::SNAKE_TAIL_RIGHT }; snakeImg.Draw(); }	//Left
		}
	}

	void Snake::ResetSnakeOnDeath(Mode mode) {
		coordsRegister.clear();
		dirRegister.clear();
		coordsRegister.push_back({ 1, 1 });
		coordsRegister.push_back({ 1, 1 });
		coordsRegister.push_back({ 1, 1 });

		SetSnakeInicialPos(mode);

		dirRegister.push_back(DIR_RIGHT);
		dirRegister.push_back(DIR_RIGHT);
		dirRegister.push_back(DIR_RIGHT);

	}

}