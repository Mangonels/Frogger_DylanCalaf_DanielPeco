#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "GameScene.hh"
#include "RankingScene.hh"
#include "IOManager.hh"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace Logger;

RankingScene::RankingScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };
	rankingSlots = 10;
	resultsEasy.resize(rankingSlots);
	resultsMedium.resize(rankingSlots);
	resultsHard.resize(rankingSlots);
	ReadBinaryFile();
}

RankingScene::~RankingScene(void) {

}

void RankingScene::SetCurDifficulty(string diff) {
	//gets difficulty from gamescene
	difficulty = diff;
}
void RankingScene::GetNewScore(int s) {
	//recibe el score
	newScore = s;
}
void RankingScene::OnEntry(void) {
	displayRanking = false;
	newPlayerName = "";
	charCounter = 0;
}
void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {

	//if the newscore is greater than 0, the game will ask a name to the player until he/she presses Enter
	if (newScore > 0) {
		
		if (IM.IsKeyDown<KEY_BUTTON_ENTER>() && charCounter > 0) {
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
			mouseCoords = IM.GetMouseCoords();
		}
		else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {

			if (mouseCoords.x > 775 && mouseCoords.x < 863 && mouseCoords.y > 284 && mouseCoords.y < 330) { //Ranking
				cout << "Selected Easy ranking" << endl;
				difficulty = "easy";
			}
			else if (mouseCoords.x > 748 && mouseCoords.x < 889 && mouseCoords.y > 360 && mouseCoords.y < 406) { //Ranking
				cout << "Selected Medium ranking" << endl;
				difficulty = "medium";
			}
			else if (mouseCoords.x > 775 && mouseCoords.x < 863 && mouseCoords.y > 436 && mouseCoords.y < 483) { //Ranking
				cout << "Selected Hard ranking" << endl;
				difficulty = "hard";
			}
			else if (mouseCoords.x > 404 && mouseCoords.x < 620 && mouseCoords.y > 591 && mouseCoords.y < 637) { //Ranking
				cout << "Menu Scene" << endl;
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
		//prints ranking
		SeeResults(difficulty);
		GUI::DrawTextBlended<FontID::FACTORY>("RANKING  -  " + difficulty,
		{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
		{ 190, 0, 160 });

		GUI::DrawTextShaded<FontID::ARIAL>("Easy", 
		{ int(W.GetWidth()*.8f), int(W.GetHeight()*.4f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });

		GUI::DrawTextShaded<FontID::ARIAL>("Medium",
		{ int(W.GetWidth()*.8f), int(W.GetHeight()*.5f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });

		GUI::DrawTextShaded<FontID::ARIAL>("Hard", 
		{ int(W.GetWidth()*.8f), int(W.GetHeight()*.6f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
	}
	else {
		//asks the player's name
		GUI::DrawTextBlended<FontID::ARIAL>("Please enter a new player name",
		{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
		{ 0, 0, 0 });

		GUI::DrawTextBlended<FontID::ARIAL>("Name:  " + newPlayerName,
		{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
		{ 0, 0, 0 });

		if (charCounter > 0) {
			GUI::DrawTextBlended<FontID::ARIAL>("Press Enter to continue",
			{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
			{ 0, 0, 0 });
		}

	}

		GUI::DrawTextShaded<FontID::ARIAL>("Exit to menu", //Back To Menu
		{ W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
		GUI::DrawTextShaded<FontID::ARIAL>("Leave", //Exit the game
		{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
		{ 115, 0, 180 }, { 50, 200, 230 });
}

void RankingScene::InsertResultInOrder(string diff, Result playerResult) { //<-Insert the new player result here
	
	list<Result> results; //with this temporary we don't have to write the same function 3 times
	if (diff == "easy") results = resultsEasy;
	else if (diff == "medium") results = resultsMedium;
	else if (diff == "hard") results = resultsHard;

		if (results.empty()) results.emplace_front(playerResult); //If there's nothing, we set the results directly on first place.
		else {
			for (list<Result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) { //"results" list iterator
				if (iterator->score < playerResult.score) { //when this condition is true means that the iterator is in the correct position
					results.insert(iterator, playerResult);
					results.resize(rankingSlots); //This removes lower scores
					break;
				}
			}
		}
		if (diff == "easy") resultsEasy = results;
		else if (diff == "medium") resultsMedium = results;
		else resultsHard = results;
}

void  RankingScene::WriteOnBinaryFile(string diff) {

	ResultBinary resultArray[10]; //makes an array to write on the file
	list<Result> results;
	string file;
	//updates the binary file
	if (diff == "easy") {
		results = resultsEasy;
		file = "../../res/dat/scoresEasy.dat";
	}
	else if (diff == "medium") {
		results = resultsMedium;
		file = "../../res/dat/scoresMedium.dat";
	}
	else {
		results = resultsHard;
		file = "../../res/dat/scoresHard.dat";
	}

	int i = 0;
	for (list<Result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
		//copies the content of the list to the array
		resultArray[i].score = iterator->score;

		string str = iterator->player;
		//makes the new char[string size] out of a string
		char *player = new char[str.size() + 1];
		copy(str.begin(), str.end(), player);
		player[str.size()] = '\0'; 
		//copies the previous char to the one from ResultBinary
		for (int j = 0; j < sizeof(resultArray[i].player); j++) {
			resultArray[i].player[j] = player[j];
		}
		delete[] player;

		fstream outfile(file, ios::out | ios::binary);
		outfile.write(reinterpret_cast<char *>(&resultArray), sizeof(resultArray));
		outfile.close();

		i++;
	}

}

void RankingScene::ReadBinaryFile() {

	ResultBinary resultArray[10]; //temporary to read the information
	
	for (int i = 0; i < 3; i++) {
		list<Result> results; //with this temporary we don't have to write the same function 3 times
		string file;
		//this loop changes the content of results and file every time, so every ranking gets updated
		if (i == 0) {
			results = resultsEasy;
			file = "../../res/dat/scoresEasy.dat";
		}
		if (i == 1) {
			results = resultsMedium;
			file = "../../res/dat/scoresMedium.dat";
		}
		if (i == 2) {
			results = resultsHard;
			file = "../../res/dat/scoresHard.dat";
		}

		fstream infile(file, ios::in | ios::binary);
		if (infile.is_open()) {
			infile.read(reinterpret_cast<char*>(&resultArray), sizeof(resultArray));
			//copies all the information of the array to the list
			int j = 0;
			for (list<Result>::iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
				iterator->player = resultArray[j].player;
				iterator->score = resultArray[j].score;
				j++;
			}
		}
		infile.close();
		if (i == 0) resultsEasy = results;
		if (i == 1) resultsMedium = results;
		if (i == 2) resultsHard = results;
	}
}

void RankingScene::MakeNewResult(int score, string playerName) {
	//makes the new structure, adds it to the list and updates the binary file
	Result newResult;
	newResult.score = score;
	newResult.player = playerName;
	InsertResultInOrder(difficulty, newResult);
	WriteOnBinaryFile(difficulty);
}

void RankingScene::SeeResults(string diff) {
	float startingHeight = .2f; //Height at which the ranking will start being displayed
	int position = 1;
	
	list<Result> results;
	if (diff == "easy") results = resultsEasy;
	else if (diff == "medium") results = resultsMedium;
	else results = resultsHard;

	for (list<Result>::const_iterator iterator = results.begin(), end = results.end(); iterator != end; ++iterator) {
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
	//system that checks which key is being pressed

	if (charCounter < charLength) {
		if (IM.IsKeyDown<'a'>()) {
			newPlayerName += 'a';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'b'>()) {
			newPlayerName += 'b';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'c'>()) {
			newPlayerName += 'c';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'d'>()) {
			newPlayerName += 'd';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'e'>()) {
			newPlayerName += 'e';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'f'>()) {
			newPlayerName += 'f';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'g'>()) {
			newPlayerName += 'g';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'h'>()) {
			newPlayerName += 'h';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'i'>()) {
			newPlayerName += 'i';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'j'>()) {
			newPlayerName += 'j';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'k'>()) {
			newPlayerName += 'k';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'l'>()) {
			newPlayerName += 'l';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'m'>()) {
			newPlayerName += 'm';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'n'>()) {
			newPlayerName += 'n';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'o'>()) {
			newPlayerName += 'o';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'p'>()) {
			newPlayerName += 'p';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'q'>()) {
			newPlayerName += 'q';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'r'>()) {
			newPlayerName += 'r';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'s'>()) {
			newPlayerName += 's';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'t'>()) {
			newPlayerName += 't';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'u'>()) {
			newPlayerName += 'u';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'v'>()) {
			newPlayerName += 'v';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'w'>()) {
			newPlayerName += 'w';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'x'>()) {
			newPlayerName += 'x';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'y'>()) {
			newPlayerName += 'y';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'z'>()) {
			newPlayerName += 'z';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'z'>()) {
			newPlayerName += 'z';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'1'>()) {
			newPlayerName += '1';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'2'>()) {
			newPlayerName += '2';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'3'>()) {
			newPlayerName += '3';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'4'>()) {
			newPlayerName += '4';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'5'>()) {
			newPlayerName += '5';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'6'>()) {
			newPlayerName += '6';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'7'>()) {
			newPlayerName += '7';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'8'>()) {
			newPlayerName += '8';
			charCounter += 1;
		}
		else if (IM.IsKeyDown<'9'>()) {
			newPlayerName += '9';
			charCounter += 1;
		}
	}
	if (IM.IsKeyDown<KEY_BUTTON_BACKSPACE>() && charCounter > 0) {
		if (newPlayerName.size() > 0) newPlayerName.pop_back();
		charCounter -= 1;
	}
	
}