#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "MenuScene.hh"
#include "RankingScene.hh"
#include "IOManager.hh"

using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameScene::GameScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	level = 0;
	paused = false;
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry() {	
	paused = false;
	pauseCounter = 0;
	totalFrogs = 0;
	level = 1;
	m_score = 0;
	vehiculos.NewLevel(level);
	insectos.reset();
	player.ResetPos();
}

void GameScene::OnExit(void) {
}

void GameScene::setCurDifficulty(std::string difficulty){
	//<Insertar aqui + metodos para rellenar el juego>
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

void GameScene::Update(void) {

	timeCounter = SDL_GetTicks();
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
	}
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) { //Pausar el juego
		
		mouseCoords.x = 0; //<- We make sure these are set to 0 in order to fix a bug where certain buttons are pressed right on display if the coords where saved at it's location.
		mouseCoords.y = 0;
		if (paused == true) paused = false;
		else {
			paused = true;
			pauseCounter = SDL_GetTicks();
		}
	}
	if (paused == false) {
		if (player.getLives() > 0 && totalFrogs < 5 && timeCounter < initialTime) {
			if (pauseCounter != 0) {
				initialTime += SDL_GetTicks() - pauseCounter;
				pauseCounter = 0;
			}

			vehiculos.update();
			troncos.update();
			tortugas.update();
			insectos.update();
			
			player.onObjectFunction(troncos.collisions(player.getCoords(), player.getSize()),
				tortugas.collisions(player.getCoords(), player.getSize()),
				insectos.collisions(player.getCoords(), player.getSize(), m_score, totalFrogs));
			player.carHitFunction(vehiculos.collisions(player.getCoords(), player.getSize()));

			player.update(m_score);

			vehiculos.SetSpeedModifier(initialAgentSpeed + round(m_score / speedPerScore));
			troncos.SetSpeedModifier(initialAgentSpeed + round(m_score / speedPerScore));
			tortugas.SetSpeedModifier(initialAgentSpeed + round(m_score / speedPerScore));

		}
		//cuando las 5 ranas se completan se sube de nivel
		else if (totalFrogs == 5 && player.getLives() > 0) {
			totalFrogs = 0;
			level += 1;
			vehiculos.NewLevel(level);
			insectos.reset();
			player.ResetPos();
		}
		//cuando el jugador se queda sin tiempo
		else if (timeCounter > initialTime && player.getLives() > 0) {
			player.TimeOut();
			initialTime += timeInterval;
		}
		else {
			SM.SetCurScene<RankingScene>("");
		}

		if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) {
			player.checkArrowKey(KEY_BUTTON_DOWN);
		}
		else if (IM.IsKeyDown<KEY_BUTTON_UP>()) {
			player.checkArrowKey(KEY_BUTTON_UP);
		}
		else if (IM.IsKeyDown<KEY_BUTTON_LEFT>()) {
			player.checkArrowKey(KEY_BUTTON_LEFT);
		}
		else if (IM.IsKeyDown<KEY_BUTTON_RIGHT>()) {
			player.checkArrowKey(KEY_BUTTON_RIGHT);
		}
	}
	//pause events
	else {
		if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 283 && mouseCoords.y < 329) { //Back To First Phase Menu
				std::cout << "Went Back To Menu Scene" << std::endl;
				SM.SetCurScene<MenuScene>("");
			}
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 360 && mouseCoords.y < 408) { //Leave the game entirely
				exit(0);
			}
		}
	}
}

void GameScene::Draw(void) {
	m_background.Draw();

	if (player.getLives() > 0 && totalFrogs < 5 && timeCounter < initialTime) {
		// Render background
		vehiculos.draw();
		troncos.draw();
		tortugas.draw();
		insectos.draw();
		player.draw();
	}
	
	if (paused == false) {
		GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(m_score),
		{ int(W.GetWidth()*.1f), int(W.GetHeight()*.97f), 1, 1 },
		{ 255, 255, 255 }); // Render score that will be different when updated

		GUI::DrawTextBlended<FontID::ARIAL>("Time: " + std::to_string(1 + (initialTime - timeCounter) / 1000),
		{ int(W.GetWidth()*.5f), int(W.GetHeight()*.97f), 1, 1 },
		{ 255, 255, 255 }); // Render score that will be different when updated

		GUI::DrawTextBlended<FontID::ARIAL>("Lives: " + std::to_string(player.getLives()),
		{ int(W.GetWidth()*.9f), int(W.GetHeight()*.97f), 1, 1 },
		{ 255, 255, 255 }); //show lives
	}
	else {
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
