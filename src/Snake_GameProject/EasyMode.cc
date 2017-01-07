#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "EasyMode.hh"

using namespace Logger;
using namespace std;

EasyMode::EasyMode(void) {
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	//		########  ####  ######  ##     ##    ###    
	//		##     ##  ##  ##    ## ##     ##   ## ##   
	//		##     ##  ##  ##       ##     ##  ##   ##  
	//		########   ##   ######  ######### ##     ## 
	//		##         ##        ## ##     ## ######### 
	//		##         ##  ##    ## ##     ## ##     ## 
	//		##        ####  ######  ##     ## ##     ## 
	//printedSnake = { { 120 + CELL / 2 + (CELL * snake.coordsRegister->x), 120 + CELL / 2 + (CELL * snake.coordsRegister->y), CELL, CELL }, ObjectID::BG_00 };
}

EasyMode::~EasyMode(void) {
}

void EasyMode::OnEntry(void) {
	beatedHighScore = false;
	fruit.fruitCoord = fruit.SpawnFruit();
	score.score = 0;
	score.lifes = 3;
}

void EasyMode::OnExit(void) {
}

void EasyMode::Update(void) {
	snake.moveSnake();
	if (fruit.EatFruit(snake)) {
		do {
			fruit.fruitCoord = fruit.SpawnFruit();
			score.addScore();
		}
		while (snake.CheckPosition(fruit.fruitCoord));
	}
	//CheckColls with walls ==> if true -1 vida.
	/*if (snake.CheckPosition(map.walls)) { // Esto de map.walls ES UN EJEMPLO DE USO
		score.decreaseLifes();
	}*/

	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
	}
}

void EasyMode::Draw(void) {
	//DRAW MAP

	background.Draw();
	fruit.drawFruit().Draw();
	snake.drawSnake().Draw();


	GUI::DrawTextBlended<FontID::PIXEL>("Score: " + to_string(score.score), //Message
		{ W.GetWidth() >> 3, 50, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB

	if (beatedHighScore) {
		GUI::DrawTextBlended<FontID::PIXEL>("HighScore: " /*+ to_string(m_score)*/, //Message
		{ 600, 50, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB
	} else if (!beatedHighScore) {
		GUI::DrawTextBlended<FontID::PIXEL>("HighScore: " /*+ to_string(m_highscore)*/, //Message
		{ 600, 50, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB
	}

	GUI::DrawTextBlended<FontID::PIXEL>("Lifes: " + to_string(score.lifes), //Message
		{ W.GetWidth() >> 3, 100, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB

	GUI::DrawTextBlended<FontID::PIXEL>("EASY MODE", //Message
		{ 600, 100, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB
}
