#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "GameScene.hh"
#include "MenuScene.hh"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
		R.LoadFont<FontID::RAKOON>("fnt/rakoon.ttf", 80);
		R.LoadTexture<ObjectID::CELL_EMPTY>("gfx/empty.png");
		R.LoadTexture<ObjectID::CANDY_BLUE>("gfx/blue.png");
		R.LoadTexture<ObjectID::CANDY_RED>("gfx/red.png");
		R.LoadTexture<ObjectID::CANDY_ORANGE>("gfx/orange.png");
		R.LoadTexture<ObjectID::CANDY_PURPLE>("gfx/purple.png");
		R.LoadTexture<ObjectID::CANDY_GREEN>("gfx/green.png");
		R.LoadTexture<ObjectID::CANDY_YELLOW>("gfx/yellow.png");
		R.LoadTexture<ObjectID::BG_00>("gfx/bg_game.jpg");
		R.LoadTexture<ObjectID::BG_01>("gfx/bg_menu.jpg");
		R.LoadTexture<ObjectID::FROG>("gfx/rana.png");
		R.LoadTexture<ObjectID::VEHICLE1>("gfx/vehiculo1.png");
		R.LoadTexture<ObjectID::VEHICLE2>("gfx/vehiculo2.png");
		R.LoadTexture<ObjectID::VEHICLE3>("gfx/vehiculo3.png");
		R.LoadTexture<ObjectID::VEHICLE4>("gfx/vehiculo4.png");
		R.LoadTexture<ObjectID::VEHICLE5>("gfx/vehiculo5.png");
		R.LoadTexture<ObjectID::TRUNKL>("gfx/troncoL.png");
		R.LoadTexture<ObjectID::TRUNKM>("gfx/troncoM.png");
		R.LoadTexture<ObjectID::TRUNKS>("gfx/troncoS.png");
		R.LoadTexture<ObjectID::TURTLE>("gfx/tortuga.png");
		R.LoadTexture<ObjectID::INSECT>("gfx/insecto.png");
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<GameScene>();
		SM.AddScene<MenuScene>();
		SM.SetCurScene<MenuScene>();
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