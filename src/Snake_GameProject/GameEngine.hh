/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "GameScene.hh"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		// ttf - fonts
		R.LoadFont<FontID::PIXEL>("ttf/minecraft.ttf", 40);

		// sprites - images
		R.LoadTexture<ObjectID::EMPTY>("gfx/fondo.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD>("gfx/snake_cabeza.png");
		R.LoadTexture<ObjectID::SNAKE_BODY>("gfx/snake_recto.png");
		R.LoadTexture<ObjectID::SNAKE_CURVE>("gfx/snake_curva.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL>("gfx/snake_cola.png");
		R.LoadTexture<ObjectID::FRUIT>("gfx/fruta.png");
		R.LoadTexture<ObjectID::WALL>("gfx/pared.png");

		/*R.LoadTexture<ObjectID::BUTTON_EASY>("gfx/IMG_TO_ADD.png");
		R.LoadTexture<ObjectID::BUTTON_MEDIUM>("gfx/IMG_TO_ADD.png");
		R.LoadTexture<ObjectID::BUTTON_HARD>("gfx/IMG_TO_ADD.png");
		R.LoadTexture<ObjectID::BUTTON_EXIT("gfx/IMG_TO_ADD.png");
		R.LoadTexture<ObjectID::BG_00>("gfx/empty.png"); // MAIN MENU BG
		R.LoadTexture<ObjectID::BG_01>("gfx/empty.png"); // IG BG
		*/
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<GameScene>();
		SM.SetCurScene<GameScene>();
	}
	/** 
	 * Runs the game specifying the window's name and dimensions
	 * @tparam screenWidth Determines the window's width
	 * @tparam screenHeight Determines the window's height
	 * @param name Determines the window's title
	 */
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
			TM.FPSBegin(); // Calculates the time difference for deltaTime and FPS limiting purposes
			#pragma region GAME_UPDATE
				switch (m_curScene->GetState()) { // Check for the state of the screen
					case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
					case SceneState::EXIT:		m_isRunning = false; break; // Triggers an end of the game looping
					case SceneState::SLEEP: default:;
				}
			#pragma endregion
			#pragma region GAME_DRAW
				TM.FPSEnd([&]() { // Limits the FPS rendering with a lambda function as the parameter that draws the whole game
					if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
						R.Clear();			// Clear the screen buffer
						m_curScene->Draw(); // Call the draw method of the scene
						R.Render();			// Update the screen buffer with all sprites that were pushed
					}});
			#pragma endregion
		}
	}
}