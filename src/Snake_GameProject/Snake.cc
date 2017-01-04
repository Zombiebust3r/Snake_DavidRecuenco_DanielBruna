#include "Snake.hh"


void main() {
	Snake mySnake({ 0,0 });

	mySnake.moveSnake();
	mySnake.drawSnake();
	

	auto i = mySnake.coordsRegister.begin();
	printf("%d", i);
}