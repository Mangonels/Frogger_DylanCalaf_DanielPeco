#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "MenuScene.hh"
#include "RankingScene.hh"
#include "IOManager.hh"

using namespace Logger;


GameScene::GameScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	level = 0;
	paused = false;
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry() {	
	//resets stats for a new game
	paused = false;
	pauseCounter = 0;
	totalFrogs = 0;
	level = 0;
	m_score = 0;
	insectos.reset();
	player.ResetPos();
}

void GameScene::OnExit(void) {
}

void GameScene::SetCurDifficulty(std::string diff){
	difficulty = diff;
	IOManager::XMLParser("xml/Difficulties.xml", std::move(difficulty), livestoFrog, initialTime, initialAgentSpeed);
	//set lives
	player.setLives(livestoFrog);
	//set timer
	timeInterval = initialTime;

	initialTime += SDL_GetTicks();
	//set speeds
	vehiculos.SetSpeedModifier(initialAgentSpeed);
	troncos.SetSpeedModifier(initialAgentSpeed);
	tortugas.SetSpeedModifier(initialAgentSpeed);
}
void GameScene::GetNewScore(int s) {
}
void GameScene::Update(void) {

	timeCounter = SDL_GetTicks();
	timeRemaining = (initialTime - timeCounter) / 1000;
	static MouseCoords mouseCoords(0, 0);
	
	//pause system
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) { 
		
		mouseCoords.x = 0; //<- We make sure these are set to 0 in order to fix a bug where certain buttons are pressed right on display if the coords where saved at it's location.
		mouseCoords.y = 0;
		if (paused == true) {
			initialTime += SDL_GetTicks() - pauseCounter; //adds to initalTime the seconds while pause was active
			pauseCounter = 0;
			paused = false;
		}
		else {
			paused = true;
			pauseCounter = SDL_GetTicks(); //gets in when was the pause pressed
		}
	}
	if (paused == false) {
		
		if (player.GetLives() > 0 && totalFrogs < 5 && timeCounter < initialTime) {
	//in-game update
			//agent updates
			vehiculos.update();
			troncos.update();
			tortugas.update();
			insectos.update();
			//collisions
			player.OnObjectFunction(troncos.collisions(player.getCoords(), player.getSize()),
				tortugas.collisions(player.getCoords(), player.getSize()),
				insectos.collisions(player.getCoords(), player.getSize(), m_score, totalFrogs, timeRemaining));
			player.CarHitFunction(vehiculos.collisions(player.getCoords(), player.getSize()));
			player.Update(m_score);
			//modifies agent speed according to score
			vehiculos.SetSpeedModifier(initialAgentSpeed + round(m_score / speedPerScore));
			troncos.SetSpeedModifier(initialAgentSpeed + round(m_score / speedPerScore));
			tortugas.SetSpeedModifier(initialAgentSpeed + round(m_score / speedPerScore));

		}
		//when the 5 frogs get home
		else if (totalFrogs == 5 && player.GetLives() > 0) {
			totalFrogs = 0;
			level += 1;
			m_score += timeRemaining;
			vehiculos.NewLevel(level);
			insectos.reset();
			player.ResetPos();
			initialTime += (timeInterval - timeRemaining*1000); //time reset
		}
		//cuando el jugador se queda sin tiempo
		else if (timeCounter > initialTime && player.GetLives() > 0) {
			player.TimeOut(); //loses a life
			initialTime += timeInterval; //time reset
		}
		else {
			SM.SetCurScene<RankingScene>(difficulty, round(m_score));
		}
		//eventos para mover la rana
		if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) {
			player.CheckArrowKey(KEY_BUTTON_DOWN);
		}
		else if (IM.IsKeyDown<KEY_BUTTON_UP>()) {
			player.CheckArrowKey(KEY_BUTTON_UP);
		}
		else if (IM.IsKeyDown<KEY_BUTTON_LEFT>()) {
			player.CheckArrowKey(KEY_BUTTON_LEFT);
		}
		else if (IM.IsKeyDown<KEY_BUTTON_RIGHT>()) {
			player.CheckArrowKey(KEY_BUTTON_RIGHT);
		}
	}
	//pause events
	else {
		if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
			mouseCoords = IM.GetMouseCoords();
		}
		if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 283 && mouseCoords.y < 329) { //Back To First Phase Menu
				std::cout << "Went Back To Menu Scene" << std::endl;
				SM.SetCurScene<MenuScene>("", 0);
			}
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 360 && mouseCoords.y < 408) { //Leave the game entirely
				SM.ExitScene();
			}
		}
	}
}

void GameScene::Draw(void) {
	m_background.Draw();

	if (player.GetLives() > 0 && totalFrogs < 5 && timeCounter < initialTime) {
		// Render background
		vehiculos.draw();
		troncos.draw();
		tortugas.draw();
		insectos.draw();
		player.Draw();
	}
	
	if (paused == false) {
		//HUD
		GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(m_score),
		{ int(W.GetWidth()*.2f), int(W.GetHeight()*.97f), 1, 1 },
		{ 255, 255, 255 }); // Render score that will be different when updated

		GUI::DrawTextBlended<FontID::ARIAL>("Time: " + std::to_string(1 + timeRemaining),
		{ int(W.GetWidth()*.5f), int(W.GetHeight()*.97f), 1, 1 },
		{ 255, 255, 255 }); // Render score that will be different when updated

		GUI::DrawTextBlended<FontID::ARIAL>("Lives: " + std::to_string(player.GetLives()),
		{ int(W.GetWidth()*.9f), int(W.GetHeight()*.97f), 1, 1 },
		{ 255, 255, 255 }); //show lives

		GUI::DrawTextBlended<FontID::ARIAL>("Level " + std::to_string(level + 1),
		{ int(W.GetWidth()*.1f), int(W.GetHeight()*.04f), 1, 1 },
		{ 255, 255, 255 }); //show level, starting level 1. (actually it is 0)
	}
	else {
		//Botones
		GUI::DrawTextBlended<FontID::RAKOON>("GAME PAUSED",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
		{ 255, 255, 255 });
		GUI::DrawTextShaded<FontID::ARIAL>("Exit To Menu", //Back To First Phase Menu
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Leave", //Leave the game entirely
		{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
	}
}
