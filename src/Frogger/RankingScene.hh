#pragma once
#include "Sprite.hh"
#include "Scene.hh"
#include <list>

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
private:
	Sprite m_background;
};