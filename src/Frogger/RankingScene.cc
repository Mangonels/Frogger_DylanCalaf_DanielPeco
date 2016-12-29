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

RankingScene::RankingScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };
	rankingSlots = 10;
}

RankingScene::~RankingScene(void) {
}

void RankingScene::setCurDifficulty(std::string t) {

}
void RankingScene::OnEntry(void) {

}

void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {

	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());

		if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 591 && mouseCoords.y < 637) { //Ranking
		std::cout << "Menu Scene" << std::endl;
			SM.SetCurScene<MenuScene>("");
		}
		else if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 669 && mouseCoords.y < 714) { //Exit the game
			exit(0);
		}
	}
}

void RankingScene::Draw(void) {
	m_background.Draw(); // Render background

	GUI::DrawTextBlended<FontID::RAKOON>("RANKING",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 });

	GUI::DrawTextShaded<FontID::ARIAL>("Exit to menu", //Back To Menu
	{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
	{ 115, 0, 180 }, { 50, 200, 230 });
	GUI::DrawTextShaded<FontID::ARIAL>("Leave", //Exit the game
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }, { 50, 200, 230 });

}

void RankingScene::insertResultInOrder(result playerResult) { //<-Insert the new player result here
	if (results.empty) results.emplace_front(playerResult); //If there's nothing, we set the results directly on first place.
	else 
	{
		for (std::list<result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) { //"results" list iterator
			if (iterator->score < playerResult.score) //Checking if the stored score, starting from the first position onwards, is lower than what we want to insert
			{
				results.insert(iterator, playerResult); //inserts "playerResult" in its corresponding position (Before the current iterated slot).
				results.resize(rankingSlots); //Making sure the map doesn't exceed it's maximum ammount of data, and removing data beyond max_size. This should remove lower scores.
				break; //If we don't break here it will be caos.
			}
		}
	}
}

void RankingScene::seeResults(void) { //At the moment, it prints top 10 results through console
	for (std::list<result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
		cout << "Player: " << iterator->player << " Score: " << iterator->score << endl;
	}
}