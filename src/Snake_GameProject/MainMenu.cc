#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MainMenu.hh" //SIEMPRE INCLUIR EL .HH CORRESPONDIENTE!!!!
using namespace Logger;

MainMenu::MainMenu(void) {
	background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };

	// DIMENSIONES DE LOS BOTONES: 300 x 50 px
	easy = { { 0, 0, W.GetHeight(), W.GetHeight() }, ObjectID::BUTTON_EASY };
	medium = { { 0, 0, W.GetHeight(), W.GetHeight() }, ObjectID::BUTTON_MEDIUM };
	hard = { { 0, 0, W.GetHeight(), W.GetHeight() }, ObjectID::BUTTON_HARD };
	exit = { { 0, 0, W.GetHeight(), W.GetHeight() }, ObjectID::BUTTON_EXIT };

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
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {

	}

	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
}

void MainMenu::Draw(void) {
	background.Draw(); // Render background
	easy.Draw();
	medium.Draw();
	hard.Draw();
	exit.Draw();
	
	/*GUI::DrawTextShaded<FontID::FACTORY>("ENTI CRUSH",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextBlended<FontID::CANDY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated
	*/
}
