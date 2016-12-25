#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "GameScene.hh"
#include "MenuScene.hh"
#include "IOManager.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameScene::GameScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	level = 0;
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry() {	
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
	if (player.getLives() > 0 && totalFrogs < 5 && timeCounter < initialTime) {

		vehiculos.update();
		troncos.update();
		tortugas.update();
		insectos.update();

		player.onObjectFunction(troncos.collisions(player.getCoords(), player.getSize()),
			tortugas.collisions(player.getCoords(), player.getSize()),
			insectos.collisions(player.getCoords(), player.getSize(), m_score, totalFrogs));
		player.carHitFunction(vehiculos.collisions(player.getCoords(), player.getSize()));

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
	timeCounter = SDL_GetTicks();

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
	
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
	}
}

void GameScene::Draw(void) {
	m_background.Draw();

	if (player.getLives() > 0 && totalFrogs < 5 && timeCounter < initialTime) {
		player.update(m_score);
		// Render background
		vehiculos.draw();
		troncos.draw();
		tortugas.draw();
		insectos.draw();
		player.draw();
	}
	
	
	GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(m_score),
	{ int(W.GetWidth()*.1f), int(W.GetHeight()*.97f), 1, 1 },
	{ 255, 255, 255 }); // Render score that will be different when updated
	
	GUI::DrawTextBlended<FontID::ARIAL>("Time: " + std::to_string(1 + (initialTime - timeCounter)/1000),
	{ int(W.GetWidth()*.5f), int(W.GetHeight()*.97f), 1, 1 },
	{ 255, 255, 255 }); // Render score that will be different when updated

	GUI::DrawTextBlended<FontID::ARIAL>("Lives: " + std::to_string(player.getLives()),
	{ int(W.GetWidth()*.9f), int(W.GetHeight()*.97f), 1, 1 },
	{ 255, 255, 255 }); //show lives
}
