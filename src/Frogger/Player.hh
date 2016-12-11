#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Player {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	int lives;
	Sprite splayer;
public:
	Player();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void draw();
};