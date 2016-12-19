#pragma once
#include "Sprite.hh"
#include "InputManager.hh"
#include "Agents.hh"
#include "Player.hh"


Vehiculo::Vehiculo(int x, int y) {
	int coordsMultiplier = round(W.GetHeight() / 16); //Calculador de "grid"
	int sizeMultiplier = 2;

	coords.first	 = x * coordsMultiplier; //Con esto sabemos a que distancia horizontal debe aparecer el vehiculo
	coords.second	 = y * coordsMultiplier; //Altura
	size.first		 = 28 * sizeMultiplier;
	size.second		 = 24 * sizeMultiplier;

	sp.objectID = ObjectID::VEHICLE; //De que tipo de vehiculo se trata, lo mete en el struct "sp"
	sp.transform = { coords.first, coords.second, size.first, size.second };
}
std::pair<int, int> Vehiculo::getCoords() {
	return coords;
}
std::pair<int, int> Vehiculo::getSize() {
	return size;
}
bool Vehiculo::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) { //Comprueba si el vehiculo esta colisionando
	//colisión
	if (coords.second == Pcoords.second && Pcoords.first + Psize.first >= coords.first && Pcoords.first <= coords.first + size.first) { //Cojemos unicamente la altura
		std::cout << "car collision!\n";
		return true;
	}
	return false;
}

void Vehiculo::draw() {
	coords.first+=1;
	if (coords.first > W.GetWidth()) {
		coords.first = -size.first;
	}
	sp.transform = { coords.first, coords.second, size.first, size.second };

	sp.Draw();
}

setVehiculos::setVehiculos() {
	number = 10;
	for (int i = 0; i < number; i++) {
		int posy = 13 - (i % 5);
		int posx = round(rand() % 20);
		Vehiculo temp(posx, posy);
		vehiculos[i] = temp;
	}
}

bool setVehiculos::collisions(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	for (int i = 0; i < number; i++) {
		if ( vehiculos[i].collision(Pcoords, Psize) ) {
			return true;
		}
	}
	return false;
}

void setVehiculos::draw() {
	for (int i = 0; i < number; i++) {
		vehiculos[i].draw();
	}
}

Tronco::Tronco(int x, int y) {
	int coordsMultiplier = round(W.GetHeight() / 16);
	int sizeMultiplier = 2;
	int type = round(rand() % 3);
	if (type == 2) {
		coords.first =	 x * coordsMultiplier;
		coords.second =	 y * coordsMultiplier;
		size.first = 177 * sizeMultiplier;
		size.second = 21 * sizeMultiplier;
		sp.objectID = ObjectID::TRUNKL;
	}
	else if (type == 1) {
		coords.first =	 x * coordsMultiplier;
		coords.second =  y * coordsMultiplier;
		size.first = 116 * sizeMultiplier;
		size.second = 21 * sizeMultiplier;
		sp.objectID = ObjectID::TRUNKM;
	}
	else {
		coords.first = x * coordsMultiplier;
		coords.second = y * coordsMultiplier;
		size.first = 84 * sizeMultiplier;
		size.second = 21 * sizeMultiplier;
		sp.objectID = ObjectID::TRUNKS;
	}
	sp.transform = { coords.first, coords.second, size.first, size.second };
}

bool Tronco::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	//colisión
	if (coords.second == Pcoords.second && Pcoords.first + Psize.first >= coords.first && Pcoords.first <= coords.first + size.first) {
		std::cout << "trunk collision!\n";
		return true;
	}
	return false;
}

std::pair<int, int> Tronco::getCoords() {
	return coords;
}
std::pair<int, int> Tronco::getSize() {
	return size;
}
void Tronco::draw() {
	coords.first += 1;
	if (coords.first > W.GetWidth()) {
		coords.first = -size.first;
	}
	sp.transform = { coords.first, coords.second, size.first, size.second };

	sp.Draw();
}

setTroncos::setTroncos() {
	number = 10;
	for (int i = 0; i < number; i++) {
		int posy = 7 - (i % 5);
		int posx = - 10 + round(rand() % 31);
		Tronco temp(posx, posy);
		troncos[i] = temp;
	}
}

bool setTroncos::collisions(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	for (int i = 0; i < number; i++) {
		if (troncos[i].collision(Pcoords, Psize)) {
			return true;
			break;
		}
	}
	return false;
}

void setTroncos::draw() {
	for (int i = 0; i < number; i++) {
		troncos[i].draw();
	}
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