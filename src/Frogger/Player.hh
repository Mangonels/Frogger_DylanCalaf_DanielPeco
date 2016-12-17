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
public:
	Player();
	void checkArrowKey (const KeyButton &key);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void draw();
};