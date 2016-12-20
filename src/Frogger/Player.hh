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
public:
	Player();
	void checkArrowKey (const KeyButton &key);
	void onObjectFunction(bool check1, bool check2, bool check3);
	void carHitFunction (bool check);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	int getLives();
	void update();
	void draw();
};