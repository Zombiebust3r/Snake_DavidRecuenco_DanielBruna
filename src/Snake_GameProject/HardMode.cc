#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "HardMode.hh" //SIEMPRE INCLUIR EL .HH CORRESPONDIENTE!!!!

//#define dimIG 64 --> dimensiones IN GAME. ya definido en EasyMode.hh

using namespace Logger;


HardMode::HardMode(void) {
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };

}

HardMode::~HardMode(void) {
}

void HardMode::OnEntry(void) {
	beatedHighScore = false;
}

void HardMode::OnExit(void) {
}

void HardMode::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();

	}
}

void HardMode::Draw(void) {
	background.Draw();
	GUI::DrawTextBlended<FontID::PIXEL>("Score: " /*+ to_string(m_score)*/, //Message
	{ W.GetWidth() >> 3, 50, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB

	if (beatedHighScore) {
		GUI::DrawTextBlended<FontID::PIXEL>("HighScore: " /*+ to_string(m_score)*/, //Message
		{ 600, 50, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB
	}
	else if (!beatedHighScore) {
		GUI::DrawTextBlended<FontID::PIXEL>("HighScore: " /*+ to_string(m_highscore)*/, //Message
		{ 600, 50, 1, 1 }, //Transform
		{ 255, 255, 255 }); // Color RGB
	}

	GUI::DrawTextBlended<FontID::PIXEL>("Lifes: " /*+ to_string(m_lifes)*/, //Message
	{ W.GetWidth() >> 3, 100, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB

	GUI::DrawTextBlended<FontID::PIXEL>("HARD MODE", //Message
	{ 600, 100, 1, 1 }, //Transform
	{ 255, 255, 255 }); // Color RGB
}