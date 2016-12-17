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


EasyMode::EasyMode(void) {
	// obj = { { posX, posY, ancho, alto }, ID };
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };

}

EasyMode::~EasyMode(void) {
}

void EasyMode::OnEntry(void) {
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

}
