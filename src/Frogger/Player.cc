#include <ctime>
#include "Player.hh"
#include "Window.hh"
#include "TimeManager.hh"

Player::Player() {
	/* movement system of the frog is based on a grid, the movement is decided by 1 * coordsMultiplier, which is the height of
	the screen divided by 16, this is because the frog has to move forward a total of 12 times. Then we wanted 13 rows where the
	frog can move and another 3 to set some free space for the score, time, lives, etc.
	*/
	
	coordsMultiplier = round(W.GetHeight() /16);
	sizeMultiplier = 2; //we will multiply the original size for this one (double)
	coords.first = 10 * coordsMultiplier; //initial point in our grid is the (x:10,y:14)
	coords.second = 14 * coordsMultiplier;
	size.first = 21 * sizeMultiplier;
	size.second = 17 * sizeMultiplier;
	lives = 10; //this number is just symbolical since it will be changed in the future
	splayer.objectID = ObjectID::FROG;
	onWater = false;
	splayer.transform = { coords.first, coords.second, size.first, size.second };
	
}

void Player::setLives(int l) 
{
	lives = l;
	//resets the 10 point per forward system since this function will only happen after a new game begins
	for (int i = 0; i < 12; i++) {
		newLines[i] = false;
	}
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
	//this function receives if a collision happened, if so, the effects to the player will me made via update or moveonobject
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

	//goal
	if (onGoal) {
		ResetPos();
		//reiniciamos bools de newlines
		for (int i = 0; i < 12; i++) {
			newLines[i] = false;
		}
	}
	//death
	else if (onTrunk == false && onTurtle == false && onWater || carHit) {
		ResetPos();
		lives--;
	}
	
	//adding 10 points for new lines
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