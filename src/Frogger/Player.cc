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
	lives = 10;
	splayer.objectID = ObjectID::FROG;
	onWater = false;
	splayer.transform = { coords.first, coords.second, size.first, size.second };
	for (int i = 0; i < 12; i++) {
		newLines[i] = false;
	}
}

void Player::setLives(int l) 
{
	lives = l;
}
void Player::TimeOut() {
	lives--;
}

void Player::ResetPos() {
	coords.first = 10 * coordsMultiplier;
	coords.second = 14 * coordsMultiplier;
}
void Player::checkArrowKey(const KeyButton &key) {
	if (key == KEY_BUTTON_DOWN) {
		if (coords.second < 14 * coordsMultiplier) {
			coords.second += 1 * coordsMultiplier;
		}
	}
	else if (key == KEY_BUTTON_UP) {
		coords.second -= 1 * coordsMultiplier;
	}
	else if (key == KEY_BUTTON_LEFT) {
		if (coords.first > 0 * coordsMultiplier) {
			coords.first -= 1 * coordsMultiplier;
		}
	}
	else if (key == KEY_BUTTON_RIGHT) {
		if (coords.first < 21 * coordsMultiplier) {
			coords.first += 1 * coordsMultiplier;
		}
	}
	splayer.transform = { coords.first, coords.second, size.first, size.second };
	
	std::cout << "frog position: { " << coords.first / coordsMultiplier << ", " << coords.second / coordsMultiplier << " } \n";
}

void Player::onObjectFunction(std::pair <bool, int>  checkTrunk, std::pair <bool, int> checkTurtle, bool checkGoal) {
	onTrunk = checkTrunk.first;
	onTurtle = checkTurtle.first;
	onGoal = checkGoal;
	if (checkTrunk.first) MoveOnObject(checkTrunk.second);
	if (checkTurtle.first) MoveOnObject(checkTurtle.second);
}
void Player::MoveOnObject(int speed) {
	coords.first += speed;
}
void Player::carHitFunction(bool check) {
	carHit = check;
}
std::pair<int, int> Player::getCoords() {
	return coords;
}
std::pair<int, int> Player::getSize() {
	return size;
}
int Player::getLives() {
	return lives;
}

void Player::update(int &score) {
	//water
	if (coords.second < 8 * coordsMultiplier) onWater = true;
	else onWater = false;

	//dies / win
	if (onGoal) {
		ResetPos();

		//reiniciamos bools de newlines
		for (int i = 0; i < 12; i++) {
			newLines[i] = false;
		}
	}
	else if (onTrunk == false && onTurtle == false && onWater || carHit) {
		ResetPos();
		lives--;
	}
	
	//adding points for new lines
	for (int i = 0; i < 12; i++) {
		if (newLines[i] == false && coords.second == (13 - i) * coordsMultiplier) {
			score += 10;
			newLines[i] = true;
		}
	}
}

void Player::draw() {
	splayer.transform = { coords.first, coords.second, size.first, size.second };
	splayer.Draw();
}