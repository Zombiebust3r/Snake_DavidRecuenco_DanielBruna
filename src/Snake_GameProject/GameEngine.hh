/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "MainMenu.hh"
#include "EasyMode.hh"
#include "MediumMode.hh"
#include "HardMode.hh"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		//=========================	FONTS (.ttf files) ==========================
		R.LoadFont<FontID::PIXEL>("ttf/minecraft.ttf", 40);

		//======================== SPRITES (.png files) =========================
		//SNAKE'S HEAD
		R.LoadTexture<ObjectID::SNAKE_HEAD_UP>("gfx/snake_head_up.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD_RIGHT>("gfx/snake_head_right.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD_DOWN>("gfx/snake_head_down.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD_LEFT>("gfx/snake_head_left.png");
		//SNAKE'S BODY
		R.LoadTexture<ObjectID::SNAKE_BODY_HOR>("gfx/snake_body_hor.png");
		R.LoadTexture<ObjectID::SNAKE_BODY_VERT>("gfx/snake_body_vert.png");
		//SNAKE'S CURVES
		R.LoadTexture<ObjectID::SNAKE_CURVE_1>("gfx/snake_curve1.png");
		R.LoadTexture<ObjectID::SNAKE_CURVE_2>("gfx/snake_curve2.png");
		R.LoadTexture<ObjectID::SNAKE_CURVE_3>("gfx/snake_curve3.png");
		R.LoadTexture<ObjectID::SNAKE_CURVE_4>("gfx/snake_curve4.png");
		//SNAKE'S TAIL
		R.LoadTexture<ObjectID::SNAKE_TAIL_UP>("gfx/snake_tail_up.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL_RIGHT>("gfx/snake_tail_right.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL_DOWN>("gfx/snake_tail_down.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL_LEFT>("gfx/snake_tail_left.png");
		//EMPTY CELL
		R.LoadTexture<ObjectID::EMPTY>("gfx/empty.png");
		//FRUIT
		R.LoadTexture<ObjectID::FRUIT>("gfx/fruit.png");
		//WALL
		R.LoadTexture<ObjectID::WALL>("gfx/wall.png");
		// BUTTONS
		R.LoadTexture<ObjectID::BUTTON_EASY>("gfx/button_easy.png");
		R.LoadTexture<ObjectID::BUTTON_MEDIUM>("gfx/button_medium.png");
		R.LoadTexture<ObjectID::BUTTON_HARD>("gfx/button_hard.png");
		R.LoadTexture<ObjectID::BUTTON_EXIT>("gfx/button_exit.png");
		// BAR
		R.LoadTexture<ObjectID::TIMEBAR>("gfx/timebar.png");
		//BGs
		R.LoadTexture<ObjectID::BG_00>("gfx/fondo.png"); // IG BG
		R.LoadTexture<ObjectID::BG_01>("gfx/mm_fondo.png"); // MAIN MENU BG

		
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<MainMenu>();
		SM.AddScene<EasyMode>();
		SM.AddScene<MediumMode>();
		SM.AddScene<HardMode>();
		SM.SetCurScene<MainMenu>();
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