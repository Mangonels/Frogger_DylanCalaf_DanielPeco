#pragma once
#include "Grid.hh"
#include "Agents.hh"
#include "Player.hh"
#include "Scene.hh"

// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void XMLSceneSetter(std::string &&difficulty);
	void Update(void) override;
	void Draw(void) override;
	
private:
	Player player;
	setVehiculos vehiculos;
	setTroncos troncos;
	setTortugas tortugas;
	setInsectos insectos;
	Sprite m_background;
	int totalFrogs { 0 };
	int m_score{ 0 };
};