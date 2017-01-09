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
	void SetCurDifficulty(std::string) override;
	void GetNewScore(int) override;
private:
	//agentes
	Player player;
	setVehiculos vehiculos;
	setTroncos troncos;
	setTortugas tortugas;
	setInsectos insectos;
	Sprite m_background;
	std::string difficulty;
	int level; //level of the game for the vehicles
	int totalFrogs { 0 }; //number of frogs that arrived to the other side
	int m_score{ 0 }; //ingame score
	int timeRemaining; 
	int timeCounter; 
	int timeInterval;
	int speedPerScore{3000}; //every 3000 , 6000m 9000 etc points the agent speed goes += 1
	int pauseCounter; //counter to know for how many seconds was the pause active
	//pause mode
	bool paused;
	//xml files
	int livestoFrog{}; //recoge las vidas del xml y las enviará a la rana
	int initialTime{}; //variable que contiene la cantidad de tiempo inicial para el jugador, pero se modifica si se utiliza el pause
	int initialAgentSpeed{}; //multiplicador de velocidad a todos los agentes que se mueven (vehiculos, troncos, coches)
};	