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
	void setCurDifficulty(std::string) override;
	void SendNewScore(int) override;

	void insertResultInOrder(Result);
	void MakeNewResult(int, std::string);
	void WriteOnBinaryFile();
	void ReadBinaryFile();
	void seeResults();
	void GetChars();
private:
	
	std::list<Result> results; //Lista ordenada
	
	int rankingSlots;
	Sprite m_background;
	int newScore;
	std::string newPlayerName;
	int charCounter = 0; //counts the number of characters being introduced in the new string
	int charLength = 7; //maximum amount of characters for the new name
	bool displayRanking{ true }; //switches between asking the player for a name or showing the ranking
};