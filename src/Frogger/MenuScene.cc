#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "GameScene.hh"
#include "RankingScene.hh"
#include "IOManager.hh"
#include <iostream>
#include <cstdlib>
//#include "IOManager.hh"

using namespace std;
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

MenuScene::MenuScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };
}

MenuScene::~MenuScene(void) {
}

void MenuScene::setCurDifficulty(std::string t) {
}
void MenuScene::SendNewScore(int s) {
}
void MenuScene::OnEntry(void) {
	initialmenu = true;
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

		if (initialmenu) {
			//In order to make two different pannels on the same menu scene, we are checking if the player is switched to difficulty selection or not.
			//Initial options menu
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 283 && mouseCoords.y < 329) { //Start
				initialmenu = false;
			}
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 437 && mouseCoords.y < 483) { //Leave
				exit(0);
			}
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 591 && mouseCoords.y < 637) { //Ranking
				cout << "Ranking Scene" << endl;
				SM.SetCurScene<RankingScene>("", 0);
			}
		}
		else //We are on the difficulty selection
		{
			//Select difficulty panels
			if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 283 && mouseCoords.y < 329) { //Easy

				cout << "Opened level Easy:" << endl;
				SM.SetCurScene<GameScene>("easy", 0);
			}
			else if (mouseCoords.x > 416 && mouseCoords.x < 610 && mouseCoords.y > 360 && mouseCoords.y < 408) { //Normal

				cout << "Opened level Medium:" << endl;
				SM.SetCurScene<GameScene>("medium", 0);
			}
			else if (mouseCoords.x > 452 && mouseCoords.x < 584 && mouseCoords.y > 436 && mouseCoords.y < 482) { //Hard

				cout << "Opened level Hard:" << endl;
				SM.SetCurScene<GameScene>("hard", 0);
			}


			else if (mouseCoords.x > 452 && mouseCoords.x < 584 && mouseCoords.y > 591 && mouseCoords.y < 637) { //Back
				initialmenu = true;
			}
		}
	}
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
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("LEAVE",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("RANKING",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
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
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Medium",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Hard",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });

		GUI::DrawTextShaded<FontID::ARIAL>("Back",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });

	}
}