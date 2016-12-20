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
}

GameScene::~GameScene(void) {
}

void GameScene::OnEntry(void) {
}

void GameScene::OnExit(void) {
}

void GameScene::XMLSceneSetter(std::string &&difficulty)
{
	int PHealth;
	int Gtime;
	int GinitSpeed;

	IOManager::XMLParser("xml/Difficulties.xml", "easy", &PHealth, &Gtime, &GinitSpeed);

	player.setLives(PHealth);

	//<Insertar aqui + funciones to lokas para rellenar el juego>
}

void GameScene::Update(void) {
	
	player.carHitFunction(vehiculos.collisions(player.getCoords(), player.getSize()));
	player.onObjectFunction(troncos.collisions(player.getCoords(), player.getSize()),
							tortugas.collisions(player.getCoords(), player.getSize()), 
							insectos.collisions(player.getCoords(), player.getSize()));
	
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
	
	vehiculos.update();
	troncos.update();
	tortugas.update();
	insectos.update();
	player.update();
	m_background.Draw(); // Render background
	vehiculos.draw();
	troncos.draw();
	tortugas.draw();
	insectos.draw();
	player.draw();
	
	/*
	GUI::DrawTextShaded<FontID::FACTORY>("ENTI CRUSH",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	*/
	GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(m_score),
	{ int(W.GetWidth()*.1f), int(W.GetHeight()*.97f), 1, 1 },
	{ 255, 255, 255 }); // Render score that will be different when updated
}
