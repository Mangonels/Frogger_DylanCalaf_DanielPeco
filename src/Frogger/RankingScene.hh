#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include <list>

struct Result
{
	std::string player;
	int score;
};

// GameScene class with the main gameplay mode

class RankingScene : public Scene {
public:
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void setCurDifficulty(std::string) override;
	void SendNewScore(int) override;

	void insertResultInOrder(Result);
	void MakeNewResult(int);
	void seeResults();
private:
	std::list<Result> results; //Lista ordenada.
	int rankingSlots;
	Sprite m_background;

	int newScore;
	Result r1{ "pingas1", 10000 };
	Result r2{ "pingas2", 9000 };
	Result r3{ "pingas3", 11140 };
	Result r4{ "pingas4", 190 };
	Result r5{ "fsopfwfjw", 1111190 };
	Result r6{ "p4342", 10 };
	Result r7{ "suspendido", 0 };

};