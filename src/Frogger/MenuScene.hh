#pragma once
#include "Sprite.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class MenuScene : public Scene {
public:
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void setCurDifficulty(std::string) override;
	void SendNewScore(int) override;
private:
	Sprite m_background;
	bool initialmenu; //A bool is enough for checking the group of buttons we want.
};