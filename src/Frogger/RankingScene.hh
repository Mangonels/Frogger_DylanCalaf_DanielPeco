#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include <list>

// GameScene class with the main gameplay mode

class RankingScene : public Scene {
public:
	struct Result{
		std::string player;
		int score;
	};
	struct ResultBinary {
		char player[8] = "";
		int score;
	};
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override; 
	void Update(void) override;
	void Draw(void) override;
	void SetCurDifficulty(std::string) override;
	void GetNewScore(int) override;

	void InsertResultInOrder(std::string , Result);
	void MakeNewResult(int, std::string);
	void WriteOnBinaryFile(std::string);
	void ReadBinaryFile();
	void SeeResults(std::string);
	void GetChars();
private:
	
	std::string difficulty;
	std::list<Result> resultsEasy; //Lista ordenada
	std::list<Result> resultsMedium;
	std::list<Result> resultsHard;
	int rankingSlots;
	Sprite m_background;
	int newScore;
	std::string newPlayerName;
	int charCounter = 0; //counts the number of characters being introduced in the new string
	int charLength = 7; //maximum amount of characters for the new name
	bool displayRanking{ true }; //switches between asking the player for a name or showing the ranking
};