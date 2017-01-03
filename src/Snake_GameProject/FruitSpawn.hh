#include <list>
#include "Snake.hh"

class FruitSpawn {
public:
	Coord fruitCoord;

	void SpawnFruit() {
		fruitCoord.x = rand() % 100;
		fruitCoord.y = rand() % 100;
		Snake::CheckPosition(fruitCoord);    //ET VOILA
	}
};