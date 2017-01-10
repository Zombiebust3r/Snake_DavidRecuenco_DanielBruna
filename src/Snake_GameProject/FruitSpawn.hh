#pragma once
#include <list>
#include "Snake.hh"

namespace {
	class FruitSpawn {

	public:
		Coord fruitCoord;
		Sprite fruit;

		FruitSpawn::FruitSpawn();
		FruitSpawn::~FruitSpawn();
		FruitSpawn(Coord f_coords);

		//Spawns a fruit checking that this one will not be spawned inside the snake
		//! This function is used everytime the snake eats a fruit, but this function has to be called in the entry of the Scene
		Coord SpawnFruit(Mode mode);

		//Detects if coordsRegister.begin (snake's head) is the same as the fruit's coords
		bool EatFruit(Snake p_snake);

		//Checks the amount of fruits the snake has eaten, depending of the level difficulty this amount will be higher or smaller
		//! When the amount is reached the player goes to the next level
		bool CheckFruits(Mode mode, int fruitsEaten);

		//Draws the fruit in its own coords
		Sprite drawFruit();
	};

	FruitSpawn::FruitSpawn() {}
	FruitSpawn::~FruitSpawn() {}
	FruitSpawn::FruitSpawn(Coord f_coords) {
		fruitCoord = f_coords;
	}

	Coord FruitSpawn::SpawnFruit(Mode mode) {
		switch (mode) {
		case EASY:
			fruitCoord.x = rand() % 74 + 2;
			fruitCoord.y = rand() % 39 + 2;
			break;
		case MEDIUM:
			fruitCoord.x = rand() % 29 + 2;
			fruitCoord.y = rand() % 15 + 2;
			break;
		case HARD:
			fruitCoord.x = rand() % 14 + 2;
			fruitCoord.y = rand() % 7 + 2;
			break;
		}
		return fruitCoord;
	}

	bool FruitSpawn::EatFruit(Snake p_snake) {
		if ((p_snake.coordsRegister.begin()->x == fruitCoord.x) && (p_snake.coordsRegister.begin()->y == fruitCoord.y)) { return true; }
		else { return false; }
	}

	bool FruitSpawn::CheckFruits(Mode mode, int fruitsEaten) {
		switch (mode) {
		case EASY:
			if (fruitsEaten == 20 * (EASY + 1)) return true;
				break;
		case MEDIUM:
			if (fruitsEaten == 20 * (MEDIUM + 1)) return true;
				break;
		default: return false; break;
		}
		return false;
	}

	Sprite FruitSpawn::drawFruit() {
		fruit = { { ((CELL / 2) + (fruitCoord.x*CELL)), ((120 + (CELL / 2)) + (fruitCoord.y*CELL)), CELL, CELL }, ObjectID::FRUIT };
		return fruit;
	}
}