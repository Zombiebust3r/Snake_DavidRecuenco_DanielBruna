#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "MediumMode.hh" //SIEMPRE INCLUIR EL .HH CORRESPONDIENTE!!!!

//#define dimIG 64 --> dimensiones IN GAME. ya definido en EasyMode.hh

using namespace Logger;


MediumMode::MediumMode(void) {
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };

}

MediumMode::~MediumMode(void) {
}

void MediumMode::OnEntry(void) {
}

void MediumMode::OnExit(void) {
}

void MediumMode::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();

	}
}

void MediumMode::Draw(void) {
	background.Draw();

}