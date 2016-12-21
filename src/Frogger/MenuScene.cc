#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "GameScene.hh"
#include "IOManager.hh"
#include <iostream>
#include <cstdlib>
//#include "IOManager.hh"

using namespace std;
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
		
		if (initialmenu) { //In order to make two different pannels on the same menu scene, we are checking if the player is switched to difficulty selection or not.
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 355 && mouseCoords.y < 415) {
				initialmenu = false;

			}
			if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 510 && mouseCoords.y < 570) {
				exit(0);
			}
		}
		else //We are on the difficulty selection
		{
			//select difficulty panels
			//easy
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 355 && mouseCoords.y < 415) { //Easy
				
				//XMLSceneSetter("easy"); <-WIP
				cout << "Opened level Easy:" << endl;
				SM.SetCurScene<GameScene>("easy");

			}
			//medium
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 510 && mouseCoords.y < 570) { //Normal
				//TestXML("LvMedium.xml"); <-WIP
				SM.SetCurScene<GameScene>("medium");
				cout << "Opened level Medium:" << endl;
			}
			//hard
			else if (mouseCoords.x > 452 && mouseCoords.x < 584 && mouseCoords.y > 660 && mouseCoords.y < 715) { //Hard
				//TestXML("LvHard.xml"); <-WIP
				SM.SetCurScene<GameScene>("hard");
				cout << "Opened level Hard:" << endl;
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
		GUI::DrawTextBlended<FontID::RAKOON>("EXTREME FROGGER",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 190, 0, 160 }); // Render score that will be different when updated
		GUI::DrawTextBlended<FontID::ARIAL>("by Dylan Calaf and Daniel peco",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
		{ 190, 0, 160 });
		GUI::DrawTextShaded<FontID::ARIAL>("START",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("LEAVE",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
	}
	else 
	{
		GUI::DrawTextBlended<FontID::RAKOON>("EXTREME FROGGER",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 190, 0, 160 });
		GUI::DrawTextBlended<FontID::ARIAL>("by Dylan Calaf and Daniel peco",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
		{ 190, 0, 160 });
		GUI::DrawTextShaded<FontID::ARIAL>("Easy",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Medium",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Hard",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
	}
}