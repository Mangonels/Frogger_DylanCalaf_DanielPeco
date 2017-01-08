#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Player {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	int coordsMultiplier, sizeMultiplier;
	int lives;
	Sprite splayer;
	bool onWater;
	bool onTrunk;
	bool onTurtle;
	bool onGoal;
	bool carHit;
	bool newLines[12];
public:
	Player();
	void setLives(int l);
	void ResetPos();
	void CheckArrowKey (const KeyButton &key); //keyboard events ingame
	void OnObjectFunction(std::pair <bool, int>  check1, std::pair <bool, int> check2, bool check3); //checks collisions for trunk insect turtle
	void MoveOnObject(int speed); //moves the frog in case onobjectfunction gets true
	void CarHitFunction (bool check); //car collision
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	int GetLives();
	void TimeOut();
	void Update(int &score);
	void Draw();
};