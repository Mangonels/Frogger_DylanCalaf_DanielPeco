#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include <list>

struct result
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
	void insertResultInOrder(result);
	void seeResults();
private:
	std::list<result> results; //Lista ordenada.
	int rankingSlots;
	Sprite m_background;

	result r1{ "pingas1", 10000 };
	result r2{ "pingas2", 9000 };
	result r3{ "pingas3", 11140 };
	result r4{ "pingas4", 190 };
	result r5{ "fsopfwfjw", 1111190 };
	result r6{ "p4342", 10 };
	result r7{ "suspendido", 0 };

};