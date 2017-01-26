#include "GUI.hh"
#include "System.hh"
#include "ID.hh"
#include "EasyMode.hh"
#include "MainMenu.hh"
#include "MediumMode.hh"

using namespace Logger;

EasyMode::EasyMode(void) : grid(EASY){
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

EasyMode::~EasyMode(void) {
}

void EasyMode::OnEntry(void) {
	cout << endl << "EASY MODE" << endl;
	snake.ResetSnakeOnDeath(EASY);
	snake.GiveGridLimits(EASY);
	snake.SetSnakeInicialPos(EASY);
	grid.SetGrid(EASY);
	mode = 1;
	fruitsEaten = 0;
	fruitCount = 0;
	highscore = 0;
	fruit.fruitCoord = fruit.SpawnFruit(EASY);
	score.score = 0;
	score.lifes = 3;
	tiempoEjecutar = 2000;
	tiempoInicial = SDL_GetTicks();
	timer.time = W.GetWidth();
}

void EasyMode::OnExit(void) {
}

void EasyMode::Update(void) {
	if (SDL_GetTicks() >= tiempoEjecutar) {
		//Utilizado para variar la velocidad de la serpiente según el nivel. No podemos hacer que aumente con el score porque coge velocidades demasiado altas y en nivel difícil no se puede jugar.
		tiempoEjecutar += 170;
		if (tiempoEjecutar - tiempoInicial >= 170) {
			tiempoInicial = tiempoEjecutar;
			snake.moveSnake();
			if (snake.CollisionsWallSnake() || timer.timer(EASY)) {
				snake.ResetSnakeOnDeath(EASY);
				fruitCount = 0; // Fruit score bonus reset
				if (score.decreaseLifes()) {
					timer.resetTimer();
					if (score.score > highscore) cout << "Best score: " << score.score << endl;
					else if (score.score < highscore) cout << "Best score: " << highscore << endl;
					SM.SetCurScene<MainMenu>();
				}
				if (score.score > highscore) highscore = score.score;
				score.score = 0;
				timer.resetTimer();
			}
		}
	}
	snake.GetKeys();

	if (fruit.EatFruit(snake)) {
		fruitsEaten++;
		fruitCount++;
		do {
			fruit.fruitCoord = fruit.SpawnFruit(EASY);
		}
		while (snake.CheckPosition(fruit.fruitCoord));
		snake.IncreaseSize();
		score.addScore(fruitCount);
		if (fruit.CheckFruits(EASY, fruitsEaten)) {
			SM.SetCurScene<MediumMode>();
		}
	}
}

void EasyMode::Draw(void) {

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

	GUI::DrawTextBlended<FontID::PIXEL>("EASY MODE", //Message
	{ 600, 100, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB
}
