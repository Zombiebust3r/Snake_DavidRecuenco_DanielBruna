/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	SNAKE_HEAD_UP, SNAKE_HEAD_LEFT, SNAKE_HEAD_DOWN, SNAKE_HEAD_RIGHT,	// Snake's head IDs
	SNAKE_BODY_HOR, SNAKE_BODY_VERT,									// Snake's body
	SNAKE_CURVE_1, SNAKE_CURVE_2, SNAKE_CURVE_3, SNAKE_CURVE_4,			// Snake changing its directions IDs
	SNAKE_TAIL_UP, SNAKE_TAIL_LEFT, SNAKE_TAIL_DOWN, SNAKE_TAIL_RIGHT,	// Snake's tail IDs
	FRUIT,																// Fruit ID
	EMPTY,																// Empty Cell IDs
	WALL,																// Wall IDs
	BG_00, BG_01,														// Background IDs
	BUTTON_EASY, BUTTON_MEDIUM, BUTTON_HARD, BUTTON_EXIT				// Main Menu's ID's buttons
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int { 
	PIXEL // Pixelart font (minecraft)
};