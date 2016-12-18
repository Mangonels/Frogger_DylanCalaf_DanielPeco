#include <ctime>
#include "Player.hh"
#include "Window.hh"
#include "TimeManager.hh"

Player::Player() {
	coordsMultiplier = round(W.GetHeight() /16);
	sizeMultiplier = 2.5;
	coords.first = 10 * coordsMultiplier;
	coords.second = 14 * coordsMultiplier;
	size.first = 21 * sizeMultiplier;
	size.second = 17 * sizeMultiplier;
	lives = 1;
	splayer.objectID = ObjectID::FROG;
	onWater = false;
	splayer.transform = { coords.first, coords.second, size.first, size.second };
	
}

void Player::checkArrowKey(const KeyButton &key) {
	if (key == KEY_BUTTON_DOWN) {
		coords.second += 1 * coordsMultiplier;
	}
	else if (key == KEY_BUTTON_UP) {
		coords.second -= 1 * coordsMultiplier;
	}
	else if (key == KEY_BUTTON_LEFT) {
		coords.first -= 1 * coordsMultiplier;
	}
	else if (key == KEY_BUTTON_RIGHT) {
		coords.first += 1 * coordsMultiplier;
	}
	splayer.transform = { coords.first, coords.second, size.first, size.second };

	//water
	if (coords.second < 8 * coordsMultiplier) onWater = true;
	else onWater = false;
	
	std::cout << "frog position: { " << coords.first / coordsMultiplier << ", " << coords.second / coordsMultiplier << " } \n";
}

void Player::onTrunkFunction(bool p) {
	onTrunk = p;
}
void Player::carHitFunction(bool p) {
	carHit = p;
}
std::pair<int, int> Player::getCoords() {
	return coords;
}
std::pair<int, int> Player::getSize() {
	return size;
}
void Player::draw() {
	//dies
	if (onTrunk == false && onWater || carHit) {
		coords.first = 10 * coordsMultiplier;
		coords.second = 14 * coordsMultiplier;
	}
	else if (onTrunk) {
		coords.first += 1;
	}

	splayer.transform = { coords.first, coords.second, size.first, size.second };
	if (onWater) {
		//coords.first += 1;
		splayer.transform = { coords.first, coords.second, size.first, size.second };
	}
	splayer.Draw();
}