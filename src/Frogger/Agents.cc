#pragma once
#include "Sprite.hh"
#include "InputManager.hh"
#include "Agents.hh"
#include "Player.hh"

Vehiculo::Vehiculo() {
	int coordsMultiplier = round(W.GetHeight() / 16);
	int sizeMultiplier = 2.5;
	coords.first = 10 * coordsMultiplier;
	coords.second = 14 * coordsMultiplier;
	size.first = 28 * sizeMultiplier;
	size.second = 24 * sizeMultiplier;
	sp1.objectID = ObjectID::VEHICLE;
	sp1.transform = { coords.first, coords.second, size.first, size.second};
}
std::pair<int, int> Vehiculo::getCoords() {
	return coords;
}
std::pair<int, int> Vehiculo::getSize() {
	return size;
}
void Vehiculo::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	if (coords.second == Pcoords.second && Pcoords.first >= coords.first  && Pcoords.first + Psize.first <= coords.first + size.first) {
		std::cout << "coll";
	}
}
void Vehiculo::draw() {
	sp1.Draw();
}

Tronco::Tronco() {
	int coordsMultiplier = round(W.GetHeight() / 16);
	int sizeMultiplier = 2;
	int type = rand() % 3;
	if (type = 2) {
		coords.first = 10 * coordsMultiplier;
		coords.second = 7 * coordsMultiplier;
		size.first = 177 * sizeMultiplier;
		size.second = 21 * sizeMultiplier;
		sp2.objectID = ObjectID::TRUNKL;
	}
	else if (type = 1) {
		coords.first = 200;
		coords.second = 300;
		size.first = 116;
		size.second = 21;
		sp2.objectID = ObjectID::TRUNKM;
	}
	else {
		coords.first = 200;
		coords.second = 300;
		size.first = 84;
		size.second = 21;
		sp2.objectID = ObjectID::TRUNKS;
	}
	sp2.transform = { coords.first, coords.second, size.first, size.second };
}
std::pair<int, int> Tronco::getCoords() {
	return coords;
}
std::pair<int, int> Tronco::getSize() {
	return size;
}
void Tronco::draw() {
	sp2.Draw();
}

Tortuga::Tortuga() {

}
std::pair<int, int> Tortuga::getCoords() {
	return coords;
}
std::pair<int, int> Tortuga::getSize() {
	return size;
}
Nutria::Nutria() {

}
std::pair<int, int> Nutria::getCoords() {
	return coords;
}
std::pair<int, int> Nutria::getSize() {
	return size;
}
Cocodrilo::Cocodrilo() {

}
std::pair<int, int> Cocodrilo::getCoords() {
	return coords;
}
std::pair<int, int> Cocodrilo::getSize() {
	return size;
}
Serpiente::Serpiente() {

}
std::pair<int, int> Serpiente::getCoords() {
	return coords;
}
std::pair<int, int> Serpiente::getSize() {
	return size;
}
Insecto::Insecto() {

}
std::pair<int, int> Insecto::getCoords() {
	return coords;
}
std::pair<int, int> Insecto::getSize() {
	return size;
}
LadyFrog::LadyFrog() {

}
std::pair<int, int> LadyFrog::getCoords() {
	return coords;
}
std::pair<int, int> LadyFrog::getSize() {
	return size;
}