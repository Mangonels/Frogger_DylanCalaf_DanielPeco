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
	void Update(void) override;
	void Draw(void) override;
private:
	Grid m_grid;
	Player player;
	Vehiculo vehiculo;
	Tronco tronco;

	Sprite m_background;
	int m_score{ 0 };
};