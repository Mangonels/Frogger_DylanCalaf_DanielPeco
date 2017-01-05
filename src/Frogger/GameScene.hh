#pragma once
#include "Agents.hh"
#include "Player.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry() override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void setCurDifficulty(std::string) override;
	void SendNewScore(int) override;
private:
	Player player;
	setVehiculos vehiculos;
	setTroncos troncos;
	setTortugas tortugas;
	setInsectos insectos;
	Sprite m_background;
	int level;
	int scoreMultiplier;
	int totalFrogs { 0 };
	int m_score{ 0 };
	int timeRemaining;
	int timeCounter;
	int timeInterval;
	int speedPerScore{5000};
	int pauseCounter;
	//pause mode
	bool paused;
	//xml files
	int livestoFrog{};
	int initialTime{};
	int initialAgentSpeed{};
};	