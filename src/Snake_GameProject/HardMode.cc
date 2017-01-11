#include "GUI.hh"
#include "System.hh"
#include "ID.hh"
#include "HardMode.hh"
#include "MainMenu.hh"


using namespace Logger;


HardMode::HardMode(void) {
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };

}

HardMode::~HardMode(void) {
}

void HardMode::OnEntry(void) {
	snake.ResetSnakeOnDeath();
	snake.GiveGridLimits(HARD);
	snake.SetSnakeInicialPos();
	grid.SetGrid(HARD);
	mode = 1;
	fruitsEaten = 0;
	highscore = 0;
	fruit.fruitCoord = fruit.SpawnFruit(HARD);
	score.score = 0;
	score.lifes = 3;
	tiempoEjecutar = 2000;
	timer.time = W.GetWidth();
}

void HardMode::OnExit(void) {
}

void HardMode::Update(void) {
	if (SDL_GetTicks() >= tiempoEjecutar) {
		//Utilizado para variar la velocidad de la serpiente según el nivel. No podemos hacer que aumente con el score porque coge velocidades demasiado altas y en nivel difícil no se puede jugar.
		tiempoEjecutar += 170;
		snake.moveSnake();
		if (snake.CollisionsWallSnake() || timer.timer(HARD)) {
			snake.ResetSnakeOnDeath();
			if (score.decreaseLifes()) {
				SM.SetCurScene<MainMenu>();
			}
			if (score.score > highscore) highscore = score.score;
			score.score = 0;
			timer.resetTimer();
		}
	}
	snake.GetKeys();

	if (fruit.EatFruit(snake)) {
		fruitsEaten++;
		do {
			fruit.fruitCoord = fruit.SpawnFruit(HARD);
		} while (snake.CheckPosition(fruit.fruitCoord));
		snake.IncreaseSize();
		score.addScore(fruitsEaten);
	}
}

void HardMode::Draw(void) {

	background.Draw();
	grid.DrawGrid();
	timer.drawTimer();
	fruit.drawFruit().Draw();
	snake.drawSnake();

	GUI::DrawTextBlended<FontID::PIXEL>("Score: " + to_string(score.score), //Message
	{ W.GetWidth() >> 3, 50, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB

	GUI::DrawTextBlended<FontID::PIXEL>("HighScore: " + to_string(highscore), //Message
	{ 600, 50, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB

	GUI::DrawTextBlended<FontID::PIXEL>("Lifes: " + to_string(score.lifes), //Message
	{ W.GetWidth() >> 3, 100, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB

	GUI::DrawTextBlended<FontID::PIXEL>("HARD MODE", //Message
	{ 600, 100, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB
}