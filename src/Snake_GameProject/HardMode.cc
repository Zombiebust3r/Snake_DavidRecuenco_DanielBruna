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

}