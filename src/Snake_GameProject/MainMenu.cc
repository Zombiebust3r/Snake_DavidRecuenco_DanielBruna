#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MainMenu.hh" //SIEMPRE INCLUIR EL .HH CORRESPONDIENTE!!!!

// DIMENSIONES DE LOS BOTONES: 300 x 50 px
#define B_W 300 //button width
#define B_H 50 //button height

// BUTTONS.X = ((GAME_WIDTH/2)-(BUTTON_WIDTH/2)) = ((1024/2)-(300/2)) = 512-150 = 362
#define B_X 362
using namespace Logger;


MainMenu::MainMenu(void) {
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	

	
	easy = { { B_X, 250, B_W, B_H }, ObjectID::BUTTON_EASY };
	medium = { { B_X, 350, B_W, B_H }, ObjectID::BUTTON_MEDIUM };
	hard = { { B_X, 450, B_W, B_H }, ObjectID::BUTTON_HARD };
	exit = { { B_X, 550, B_W, B_H }, ObjectID::BUTTON_EXIT };

}

MainMenu::~MainMenu(void) {
}

void MainMenu::OnEntry(void) {
}

void MainMenu::OnExit(void) {
}

void MainMenu::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
		if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 250 && mouseCoords.y <= 250 + B_H)) {
			Println("1");
		} else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 350 && mouseCoords.y <= 350 + B_H)) {
			Println("2");
		} else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 450 && mouseCoords.y <= 450 + B_H)) {
			Println("3");
		} else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 550 && mouseCoords.y <= 550 + B_H)) {
			Println("4");
		}
	}
	
}

void MainMenu::Draw(void) {
	background.Draw();
	easy.Draw();
	medium.Draw();
	hard.Draw();
	exit.Draw();
}
