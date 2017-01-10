#pragma once
#include <list>
#include "Snake.hh"

#include "MediumMode.hh"
#include "HardMode.hh"

namespace {
	class FruitSpawn {
	private:
		int fruitsEaten;

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
		void CheckFruits(Mode mode);

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
			fruitCoord.x = rand() % 44 + 1;
			fruitCoord.y = rand() % 100 + 1;
			break;
		case MEDIUM:
			fruitCoord.x = rand() % 17 + 1;
			fruitCoord.y = rand() % 11 + 1;
			break;
		case HARD:
			fruitCoord.x = rand() % 8 + 1;
			fruitCoord.y = rand() % 6 + 1;
			break;
		}
		return fruitCoord;
	}

	bool FruitSpawn::EatFruit(Snake p_snake) {
		if ((p_snake.coordsRegister.begin()->x == fruitCoord.x) && (p_snake.coordsRegister.begin()->y == fruitCoord.y)) {
			fruitsEaten++;
			return true;
		}
		else { return false; }
	}

	void FruitSpawn::CheckFruits(Mode mode) {
		switch (mode) {
		case EASY:
			if (fruitsEaten == 5 * (EASY + 1)) //SM.SetCurScene<MediumMode>();
				break;
		case MEDIUM:
			if (fruitsEaten == 5 * (MEDIUM + 1)) //SM.SetCurScene<HardMode>();
				break;
		case HARD:
			// No limit --> End reached
			break;
		}
	}

	Sprite FruitSpawn::drawFruit() {
		fruit = { { ((CELL / 2) + (fruitCoord.x*CELL)), ((120 + (CELL / 2)) + (fruitCoord.y*CELL)), CELL, CELL }, ObjectID::FRUIT };
		return fruit;
	}
}