#include <ctime>
#include "Player.hh"
#include "Window.hh"
#include "TimeManager.hh"

Player::Player() {
	coords.first = 200;
	coords.second = 400;
	size.first = 21;
	size.second = 17;
	lives = 1;
	splayer.objectID = ObjectID::FROG;
	splayer.transform = { coords.first, coords.second, size.first, size.second };
}
std::pair<int, int> Player::getCoords() {
	return coords;
}
std::pair<int, int> Player::getSize() {
	return size;
}
void Player::draw() {
	splayer.Draw();
}