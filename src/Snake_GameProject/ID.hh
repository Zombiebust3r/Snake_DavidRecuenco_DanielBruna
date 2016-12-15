/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	SNAKE_HEAD, SNAKE_BODY, SNAKE_CURVE, SNAKE_TAIL, // Snake IDs
	FRUIT, // Fruit ID
	EMPTY, // Cell IDs
	WALL, // Wall IDs
	BG_00, BG_01,  // Background IDs
	BUTTON_EASY, BUTTON_MEDIUM, BUTTON_HARD, BUTTON_EXIT // Main Menu's ID's buttons

	, CANDY_EMPTY, CANDY_MAX, CELL_EMPTY //para que no se queje el VS
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int { 
	PIXEL // Pixelart font (minecraft)
};