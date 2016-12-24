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
	void checkArrowKey (const KeyButton &key);
	void onObjectFunction(std::pair <bool, int>  check1, bool check2, bool check3);
	void move(int speed);
	void carHitFunction (bool check);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	int getLives();
	void TimeOut();
	void update(int &score);
	void draw();
};