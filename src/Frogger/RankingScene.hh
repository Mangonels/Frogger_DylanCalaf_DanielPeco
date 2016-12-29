#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include <list>

struct result
{
	string player;
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
	void insertResultInOrder(result);
	void seeResults();
private:
	std::list<result> results; //Lista ordenada.
	int rankingSlots;
	Sprite m_background;
};