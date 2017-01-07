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
	ReadBinaryFile();
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
				SM.ExitScene();
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
			if (iterator->score < playerResult.score){
				results.insert(iterator, playerResult); 
				results.resize(rankingSlots); //Making sure the map doesn't exceed it's maximum ammount of data, and removing data beyond max_size. This should remove lower scores.
				break; //If we don't break here it will be caos.
			}
		}
	}	
}

void  RankingScene::WriteOnBinaryFile() {

	remove("../../res/scores.dat");
	
	int i = 0;
	for (std::list<Result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
		resultArray[i].player = iterator->player;
		resultArray[i].score = iterator->score;
		i++;
	}

	std::fstream outfile("../../res/scores.dat",  ios::out | ios::binary);
	outfile.write(reinterpret_cast<char *>(&resultArray), sizeof(resultArray));
	outfile.close();

}

void RankingScene::ReadBinaryFile() {

	std::fstream infile("../../res/scores.dat", ios::in | ios::binary);
	if (infile.is_open()) {
		infile.read(reinterpret_cast<char*>(&resultArray), sizeof(resultArray));
		
		int i = 0;
		for (std::list<Result>::iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
			iterator->player = resultArray[i].player;
			iterator->score = resultArray[i].score;
			i++;
		}
	}

	infile.close();
	/*
	std::list<Result> temp;
	Result temp2;

	std::ifstream infile("scores.dat", ios::in | ios::binary);
	temp.resize(10);
	for (int i = 0; i < 10; i++) {
	infile.read(reinterpret_cast<char*>(&temp2), sizeof(temp2));
	temp.push_back(temp2);
	}

	results = temp;
	*/
}

void RankingScene::MakeNewResult(int score, std::string playerName) {
	Result newResult;
	newResult.score = score;
	newResult.player = playerName;
	insertResultInOrder(newResult);
	WriteOnBinaryFile();
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
	}
}

void RankingScene::GetChars(void) {

	/*  -- este metodo es más optimo pero por alguna razón no funciona tan fluido como el otro --
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
	else if (IM.IsKeyDown<'z'>()) {
		newPlayerName += 'z';
	}
	else if (IM.IsKeyDown<'1'>()) {
		newPlayerName += '1';
	}
	else if (IM.IsKeyDown<'2'>()) {
		newPlayerName += '2';
	}
	else if (IM.IsKeyDown<'3'>()) {
		newPlayerName += '3';
	}
	else if (IM.IsKeyDown<'4'>()) {
		newPlayerName += '4';
	}
	else if (IM.IsKeyDown<'5'>()) {
		newPlayerName += '5';
	}
	else if (IM.IsKeyDown<'6'>()) {
		newPlayerName += '6';
	}
	else if (IM.IsKeyDown<'7'>()) {
		newPlayerName += '7';
	}
	else if (IM.IsKeyDown<'8'>()) {
		newPlayerName += '8';
	}
	else if (IM.IsKeyDown<'9'>()) {
		newPlayerName += '9';
	}

	else if (IM.IsKeyDown<KEY_BUTTON_BACKSPACE>()) {
		if (newPlayerName.size() > 0) newPlayerName.pop_back();
	}
}