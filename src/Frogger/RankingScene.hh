#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include <list>

// GameScene class with the main gameplay mode

class RankingScene : public Scene {
public:
	struct Result
	{
		std::string player;
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
	Result resultArray[10]; //array para escribir y leer los valores del archivo binario
	int rankingSlots;
	Sprite m_background;
	int newScore;
	std::string newPlayerName;
	bool displayRanking{ true };
};