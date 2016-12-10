#pragma once
#include "Sprite.hh"
#include "InputManager.hh"
#include "Agents.hh"

Vehiculo::Vehiculo() {
	coords.first = 200;
	coords.second = 200;
	size.first = 28;
	size.second = 24;
	sp1.objectID = ObjectID::VEHICLE;
	sp1.transform = { coords.first, coords.second, size.first, size.second};
}
std::pair<int, int> Vehiculo::getCoords() {
	return coords;
}
std::pair<int, int> Vehiculo::getSize() {
	return size;
}
void Vehiculo::draw() {
	sp1.Draw();
}

Tronco::Tronco() {
	coords.first = 200;
	coords.second = 300;
	size.first = 177;
	size.second = 21;
	sp2.objectID = ObjectID::TRUNK;
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