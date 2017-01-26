#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MainMenu.hh" //SIEMPRE INCLUIR EL .HH CORRESPONDIENTE!!!!
#include "HardMode.hh"
#include "MediumMode.hh"
#include "EasyMode.hh"

// DIMENSIONES DE LOS BOTONES: 300 x 50 px
#define B_W 300 //button width
#define B_H 50 //button height

// BUTTONS.X = ((GAME_WIDTH/2)-(BUTTON_WIDTH/2)) = ((1024/2)-(300/2)) = 512-150 = 362
#define B_X 380
using namespace Logger;


MainMenu::MainMenu(void) {
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };
	ranking_bg = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	
	easy = { { B_X, 250, B_W, B_H }, ObjectID::BUTTON_EASY };
	medium = { { B_X, 350, B_W, B_H }, ObjectID::BUTTON_MEDIUM };
	hard = { { B_X, 450, B_W, B_H }, ObjectID::BUTTON_HARD };

	ranking = { { B_X, 550, B_W, B_H }, ObjectID::BUTTON_RANKING };
	return_b = { { B_X, 650, B_W, B_H }, ObjectID::BUTTON_RETURN };

	exit = { { B_X, 650, B_W, B_H }, ObjectID::BUTTON_EXIT };

}

MainMenu::~MainMenu(void) {
}

void MainMenu::OnEntry(void) {
	cout << endl << "MAIN MENU" << endl;
	rankingMenu = false;
}

void MainMenu::OnExit(void) {
}

void MainMenu::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();
		if (!rankingMenu) {
			if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 250 && mouseCoords.y <= 250 + B_H)) {
				SM.SetCurScene<EasyMode>();
			}
			else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 350 && mouseCoords.y <= 350 + B_H)) {
				SM.SetCurScene<MediumMode>();
			}
			else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 450 && mouseCoords.y <= 450 + B_H)) {
				SM.SetCurScene<HardMode>();
			}
			else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 550 && mouseCoords.y <= 550 + B_H)) {
				rankingMenu = true;
				cout << endl << "RANKING MENU" << endl;
			}
			else if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 650 && mouseCoords.y <= 650 + B_H)) {
				SetState<SceneState::EXIT>();
			}
		} else if(rankingMenu){
			if ((mouseCoords.x >= B_X && mouseCoords.x <= B_X + B_W) && (mouseCoords.y >= 650 && mouseCoords.y <= 650 + B_H)) {
				rankingMenu = false;
				cout << endl << "MAIN MENU" << endl;
			}
		}
	}
}

void MainMenu::Draw(void) {
	
	if (!rankingMenu) {
		background.Draw();
		easy.Draw();
		medium.Draw();
		hard.Draw();
		ranking.Draw();
		exit.Draw();
	} else if (rankingMenu) {
		ranking_bg.Draw();
		return_b.Draw();
		// RANKING TITLE
		GUI::DrawTextBlended<FontID::PIXEL>("RANKING",
		{ W.GetWidth() / 2, 50, 1, 1 },
		{ 255, 255, 255 });
		// SCORES in RANKING
		GUI::DrawTextBlended<FontID::PIXEL>("1- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 150, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("2- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 200, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("3- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 250, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("4- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 300, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("5- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 350, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("6- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 400, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("7- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 450, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("8- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 500, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("9- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 550, 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextBlended<FontID::PIXEL>("10- " /*+ to_string(VARIABLE RECOGIDA DE XML)*/,
		{ W.GetWidth() / 2, 600, 1, 1 },
		{ 255, 255, 255 });
	}
}
