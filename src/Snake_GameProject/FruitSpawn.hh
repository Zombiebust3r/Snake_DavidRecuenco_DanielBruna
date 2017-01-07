#pragma once
#include <list>
#include "Grid.hh"
#include "Snake.hh"
#include "Sprite.hh"

class FruitSpawn {
public:
	Coord fruitCoord;
	Sprite fruit;

	FruitSpawn::FruitSpawn();
	FruitSpawn::~FruitSpawn();
	FruitSpawn(Coord f_coords);

	//Spawns a fruit checking that this one will not be spawned inside the snake
	//! This function is used everytime the snake eats a fruit, but this function has to be called in the entry of the Scene
	Coord SpawnFruit();

	//Detects if coordsRegister.begin (snake's head) is the same as the fruit's coords
	bool EatFruit(Snake p_snake);

	//Draws the fruit in its own coords
	Sprite drawFruit();
};

FruitSpawn::FruitSpawn() {}
FruitSpawn::~FruitSpawn() {}
FruitSpawn::FruitSpawn(Coord f_coords) {
	fruitCoord = f_coords;
}

Coord FruitSpawn::SpawnFruit() {
	fruitCoord.x = rand() % 100;
	fruitCoord.y = rand() % 100;
	return fruitCoord;
}

bool FruitSpawn::EatFruit(Snake p_snake) {
	if((p_snake.coordsRegister.begin()->x == fruitCoord.x) && (p_snake.coordsRegister.begin()->y == fruitCoord.y)) {
		return true;
	} else { return false; }
}

Sprite FruitSpawn::drawFruit() {
	fruit = { { ((CELL / 2) + (fruitCoord.x*CELL)), ((120 + (CELL / 2)) + (fruitCoord.y*CELL)), CELL, CELL }, ObjectID::FRUIT };
	return fruit;
}