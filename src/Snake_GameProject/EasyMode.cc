#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "EasyMode.hh" //SIEMPRE INCLUIR EL .HH CORRESPONDIENTE!!!!

// DIMENSIONES DE LOS ELEMENTOS: 64 x 64
// Al ser iguales, solo se hace un define para ambas longitudes
#define dimIG 64 // dimensiones IN GAME

using namespace Logger;
using namespace std;

EasyMode::EasyMode(void) {
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };

}

EasyMode::~EasyMode(void) {
}

void EasyMode::OnEntry(void) {
	beatedHighScore = false;
}

void EasyMode::OnExit(void) {
}

void EasyMode::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
		
	}
}

void EasyMode::Draw(void) {
	background.Draw();


	GUI::DrawTextBlended<FontID::PIXEL>("Score: " /*+ to_string(m_score)*/, //Message
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

	GUI::DrawTextBlended<FontID::PIXEL>("Lifes: " /*+ to_string(m_lifes)*/, //Message
		{ W.GetWidth() >> 3, 100, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB

	GUI::DrawTextBlended<FontID::PIXEL>("EASY MODE", //Message
		{ 600, 100, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB
}
