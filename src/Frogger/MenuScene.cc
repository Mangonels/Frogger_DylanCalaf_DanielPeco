#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

bool initialmenu = true; //A bool is enough for checking the group of buttons we want.

MenuScene::MenuScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();

	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
		//select difficulty panels
		//easy
		if (initialmenu) { //In order to make two different pannels on the same menu scene, we are checking if the player is switched to difficulty selection or not.
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 355 && mouseCoords.y < 415) {
				initialmenu = false;
			}
			if (mouseCoords.x > 452 && mouseCoords.x < 584 && mouseCoords.y > 660 && mouseCoords.y < 715) {
				//Cerrar ventana/salir del juego
			}
		}
		else //We are on the difficulty selection
		{
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 355 && mouseCoords.y < 415) {
				SM.SetCurScene<GameScene>();
			}
			//medium
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 510 && mouseCoords.y < 570) {
				SM.SetCurScene<GameScene>();
			}
			//hard
			else if (mouseCoords.x > 452 && mouseCoords.x < 584 && mouseCoords.y > 660 && mouseCoords.y < 715) {
				SM.SetCurScene<GameScene>();
			}
		}
	}

	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");

	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
}

void MenuScene::Draw(void) {
	m_background.Draw(); // Render background
	if (initialmenu) {
		GUI::DrawTextShaded<FontID::FACTORY>("EXTREME FROGGER",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
		GUI::DrawTextShaded<FontID::FACTORY>("by Dylan Calaf and Daniel peco",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
		{ 190, 0, 160 }, { 50, 200, 230 });
		GUI::DrawTextBlended<FontID::CANDY>("START",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 });
		GUI::DrawTextBlended<FontID::CANDY>("LEAVE",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
		{ 115, 0, 180 });
	}
	else 
	{
		GUI::DrawTextShaded<FontID::FACTORY>("EXTREME FROGGER",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 190, 0, 160 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::FACTORY>("by Dylan Calaf and Daniel peco",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
		{ 190, 0, 160 }, { 50, 200, 230 });
		GUI::DrawTextBlended<FontID::CANDY>("Easy",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 });
		GUI::DrawTextBlended<FontID::CANDY>("Medium",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
		{ 115, 0, 180 });
		GUI::DrawTextBlended<FontID::CANDY>("Hard",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
		{ 115, 0, 180 });
	}
}