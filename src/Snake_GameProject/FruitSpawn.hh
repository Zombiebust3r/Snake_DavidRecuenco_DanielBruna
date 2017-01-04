#include <list>
#include "Grid.hh"
#include "Snake.hh"

#define CELL 50 // EJEMPLO

class FruitSpawn {
public:
	Coord fruitCoord;

	Sprite fruit = { {fruitCoord.x,fruitCoord.y,CELL,CELL}, ObjectID::FRUIT };

	//Spawns a fruit chacking that this one will not be spawned inside the snake
	//! This function is used everytime the snake eats a fruit, but this function has to be called in the entry of the Scene
	void SpawnFruit();

	//Detects if coordsRegister.begin (snake's head) is the same as the fruit's coords
	void EatFruit() {
		if ((Snake::coordsRegister.begin()->x == fruitCoord.x) && (Snake::coordsRegister.begin()->y == fruitCoord.y)) {
			//points
			SpawnFruit();
		}
	}

	//Draws the fruit in its own coords
	void drawFruit();
};

void FruitSpawn::SpawnFruit() {
	fruitCoord.x = rand() % 100;
	fruitCoord.y = rand() % 100;
	Snake::CheckPosition(fruitCoord);
}

void FruitSpawn::drawFruit() {
	fruit.Draw();
}