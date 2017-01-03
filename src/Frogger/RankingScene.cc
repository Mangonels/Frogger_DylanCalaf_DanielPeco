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
	results.resize(rankingSlots);
	
	insertResultInOrder(r1);
	insertResultInOrder(r2);
	insertResultInOrder(r2);
	insertResultInOrder(r2);
	insertResultInOrder(r5);
	insertResultInOrder(r7);
}

RankingScene::~RankingScene(void) {
}

void RankingScene::setCurDifficulty(std::string t) {

}
void RankingScene::SendNewScore(int s) {
	newScore = s;
}
void RankingScene::OnEntry(void) {
	displayRanking = false;
	newPlayerName = "";
}
void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {

	if (newScore > 0) {
		
		if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
			displayRanking = true;
		}
		else {
			GetChars();

			/*
			 while (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN) {
					std::cout << "cualquier cosa";
					//Keep a copy of the current version of the string 
					std::string temp = newPlayerName;
					//If the string less than maximum size
					if (newPlayerName.length() <= 16) {
						//If the key is a space 
						if (event.key.keysym.sym >=  (Uint16)'a' && event.key.keysym.sym <= (Uint16)'z') {
							//Append the character
							newPlayerName += (char)event.key.keysym.sym;
						}
					}
				}
			}
			*/

		}
		if (displayRanking == true) {
			MakeNewResult(newScore, newPlayerName);
			newScore = 0;
		}
	}
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
				SM.SetCurScene<MenuScene>("", 0);
			}
			else if (mouseCoords.x > 455 && mouseCoords.x < 576 && mouseCoords.y > 669 && mouseCoords.y < 714) { //Exit the game
				exit(0);
			}
		}
}

void RankingScene::Draw(void) {
	m_background.Draw(); // Render background
	if (newScore == 0) {
		seeResults();

		GUI::DrawTextBlended<FontID::RAKOON>("RANKING",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 190, 0, 160 });
	}
	else {
		GUI::DrawTextBlended<FontID::ARIAL>("Please enter a new player name",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
		{ 0, 0, 0 });

		GUI::DrawTextBlended<FontID::ARIAL>("Name:  " + newPlayerName,
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 0, 0, 0 });

	}

		GUI::DrawTextShaded<FontID::ARIAL>("Exit to menu", //Back To Menu
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Leave", //Exit the game
		{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
}

void RankingScene::insertResultInOrder(Result playerResult) { //<-Insert the new player result here
	
	if (results.empty()) results.emplace_front(playerResult); //If there's nothing, we set the results directly on first place.
	else {
		for (std::list<Result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) { //"results" list iterator
			if (iterator->score < playerResult.score) //Checking if the stored score, starting from the first position onwards, is lower than what we want to insert
			{
				results.insert(iterator, playerResult); //inserts "playerResult" in its corresponding position (Before the current iterated slot).
				results.resize(rankingSlots); //Making sure the map doesn't exceed it's maximum ammount of data, and removing data beyond max_size. This should remove lower scores.
				break; //If we don't break here it will be caos.
			}
		}
	}	
}

void RankingScene::MakeNewResult(int score, std::string playerName) {
	Result newResult;
	newResult.score = score;
	newResult.player = playerName;
	insertResultInOrder(newResult);
}

void RankingScene::seeResults(void) {
	float startingHeight = .2f; //Height at which the ranking will start being displayed
	int position = 1;
	for (std::list<Result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
		GUI::DrawTextBlended<FontID::ARIAL>("#" + to_string(position) + " " + iterator->player + " Score: " + to_string(iterator->score), //Score slot construction.
		{ W.GetWidth() >> 1, int(W.GetHeight() * startingHeight), 1, 1 }, //The score slots will be inserted from startingHeight upwards.
		{ 0, 0, 0 });
		
		startingHeight += .05f; //Summed up height for next ranking slot
		position++;
		//Alternative displayer:
		// cout << "Player: " << iterator->player << " Score: " << iterator->score << endl;
	}
}

//WIP de momento, chapucero a saco XD
void RankingScene::GetChars(void) {
	/*
	for (char i = 'a'; i < 'z'; i++) {
		if (IM.IsKeyDown<i>()) {
			newPlayerName += i;
		}
	}
	*/
	if (IM.IsKeyDown<'a'>()) {
		newPlayerName += 'a';
	}
	else if (IM.IsKeyDown<'b'>()) {
		newPlayerName += 'b';
	}
	else if (IM.IsKeyDown<'c'>()) {
		newPlayerName += 'c';
	}
	else if (IM.IsKeyDown<'d'>()) {
		newPlayerName += 'd';
	}
	else if (IM.IsKeyDown<'e'>()) {
		newPlayerName += 'e';
	}
	else if (IM.IsKeyDown<'f'>()) {
		newPlayerName += 'f';
	}
	else if (IM.IsKeyDown<'g'>()) {
		newPlayerName += 'g';
	}
	else if (IM.IsKeyDown<'h'>()) {
		newPlayerName += 'h';
	}
	else if (IM.IsKeyDown<'i'>()) {
		newPlayerName += 'i';
	}
	else if (IM.IsKeyDown<'j'>()) {
		newPlayerName += 'j';
	}
	else if (IM.IsKeyDown<'k'>()) {
		newPlayerName += 'k';
	}
	else if (IM.IsKeyDown<'l'>()) {
		newPlayerName += 'l';
	}
	else if (IM.IsKeyDown<'m'>()) {
		newPlayerName += 'm';
	}
	else if (IM.IsKeyDown<'n'>()) {
		newPlayerName += 'n';
	}
	else if (IM.IsKeyDown<'o'>()) {
		newPlayerName += 'o';
	}
	else if (IM.IsKeyDown<'p'>()) {
		newPlayerName += 'p';
	}
	else if (IM.IsKeyDown<'q'>()) {
		newPlayerName += 'q';
	}
	else if (IM.IsKeyDown<'r'>()) {
		newPlayerName += 'r';
	}
	else if (IM.IsKeyDown<'s'>()) {
		newPlayerName += 's';
	}
	else if (IM.IsKeyDown<'t'>()) {
		newPlayerName += 't';
	}
	else if (IM.IsKeyDown<'u'>()) {
		newPlayerName += 'u';
	}
	else if (IM.IsKeyDown<'v'>()) {
		newPlayerName += 'v';
	}
	else if (IM.IsKeyDown<'w'>()) {
		newPlayerName += 'w';
	}
	else if (IM.IsKeyDown<'x'>()) {
		newPlayerName += 'x';
	}
	else if (IM.IsKeyDown<'y'>()) {
		newPlayerName += 'y';
	}
	else if (IM.IsKeyDown<'z'>()) {
		newPlayerName += 'z';
	}
	else if (IM.IsKeyDown<KEY_BUTTON_BACKSPACE>()) {
		if (newPlayerName.size() > 0) newPlayerName.pop_back();
	}
}