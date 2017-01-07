#pragma once
#include "Sprite.hh"
#include "InputManager.hh"
#include "Agents.hh"
#include "Player.hh"

Vehiculo::Vehiculo(int x, int y, int type) {
	int coordsMultiplier = round(W.GetHeight() / 16); //Calculador de "grid"
	int sizeMultiplier = 2;
	timeCounter = 0;
	coords.first	 = x * coordsMultiplier; //Con esto sabemos a que distancia horizontal debe aparecer el vehiculo
	coords.second	 = y * coordsMultiplier; //Altura
	switch (type) {
	case 0:
		size.first = 24 * sizeMultiplier;
		size.second = 25 * sizeMultiplier;
		speed = -1;
		timeInterval = 20;
		sp.objectID = ObjectID::VEHICLE1; //De que tipo de vehiculo se trata, lo mete en el struct "sp"
		break;
	case 1:
		size.first = 24 * sizeMultiplier;
		size.second = 21 * sizeMultiplier;
		speed = 1;
		timeInterval = 16;
		sp.objectID = ObjectID::VEHICLE2; //De que tipo de vehiculo se trata, lo mete en el struct "sp"
		break;

	case 2:
		size.first = 28 * sizeMultiplier;
		size.second = 19 * sizeMultiplier;
		speed = -1;
		timeInterval = 18;
		sp.objectID = ObjectID::VEHICLE3; //De que tipo de vehiculo se trata, lo mete en el struct "sp"
		break;
	case 3:
		size.first = 28 * sizeMultiplier;
		size.second = 24 * sizeMultiplier;
		speed = 1;
		timeInterval = 16;
		sp.objectID = ObjectID::VEHICLE4; //De que tipo de vehiculo se trata, lo mete en el struct "sp"
		break;
	case 4:
		size.first = 45 * sizeMultiplier;
		size.second = 18 * sizeMultiplier;
		speed = -1;
		timeInterval = 14;
		sp.objectID = ObjectID::VEHICLE5; //De que tipo de vehiculo se trata, lo mete en el struct "sp"
		break;
	default:
		break;
	}
	maxTimeCounter = timeInterval;
	sp.transform = { coords.first, coords.second, size.first, size.second };
}
std::pair<int, int> Vehiculo::getCoords() {
	return coords;
}
std::pair<int, int> Vehiculo::getSize() {
	return size;
}

void Vehiculo::update() {
	
	timeCounter = SDL_GetTicks();
	if (timeCounter >= maxTimeCounter && timeCounter <= maxTimeCounter + timeInterval) {
		switch (sp.objectID) {
		case ObjectID::VEHICLE1:
			coords.first += speed;
			if (coords.first < -size.first) {
				coords.first = W.GetWidth();
			}
			break;
		case ObjectID::VEHICLE2:
			coords.first += speed;
			if (coords.first > W.GetWidth()) {
				coords.first = -size.first;
			}
			break;
		case ObjectID::VEHICLE3:
			coords.first += speed;
			if (coords.first < -size.first) {
				coords.first = W.GetWidth();
			}
			break;
		case ObjectID::VEHICLE4:
			coords.first += speed;
			if (coords.first > W.GetWidth()) {
				coords.first = -size.first;
			}
			break;
		case ObjectID::VEHICLE5:
			coords.first += speed;
			if (coords.first < -size.first) {
				coords.first = W.GetWidth();
			}
			break;
		default:
			break;
		}
		maxTimeCounter += timeInterval;
	}
	else if(timeCounter > maxTimeCounter + timeInterval) {
		maxTimeCounter = timeCounter + timeInterval;
	}
}
void Vehiculo::SetSpeedModifier(int speedModifier) {
	
	switch (sp.objectID) {
	case ObjectID::VEHICLE1:
		speed = -speedModifier;
		break;
	case ObjectID::VEHICLE2:
		speed = speedModifier;
		break;
	case ObjectID::VEHICLE3:
		speed = -speedModifier;
		break;
	case ObjectID::VEHICLE4:
		speed = speedModifier;
		break;
	case ObjectID::VEHICLE5:
		speed = -speedModifier;
		break;
	default:
		break;
	}
}
bool Vehiculo::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) { //Comprueba si el vehiculo esta colisionando
	//colisión
	if (coords.second == Pcoords.second && Pcoords.first + Psize.first >= coords.first && Pcoords.first <= coords.first + size.first) { //Cogemos unicamente la altura
		return true;
	}
	return false;
}

void Vehiculo::draw() {
	
	sp.transform = { coords.first, coords.second, size.first, size.second };

	sp.Draw();
}

setVehiculos::setVehiculos() {
	number = 8;
	int split = 0;
	for (int i = 0; i < number; i++) {
		int posy = 13 - (i % 5);
		int posx = split;
		Vehiculo temp(posx, posy, i % 5);
		vehiculos[i] = temp;
		split += 2;
	}
}
void setVehiculos::SetSpeedModifier(int speedModifier) {
	for (int i = 0; i < number; i++) {
		vehiculos[i].SetSpeedModifier(speedModifier);
	}
}
void setVehiculos::update() {
	for (int i = 0; i < number; i++) {
		vehiculos[i].update();
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

void setVehiculos::NewLevel(int level) {
	number = 8 + level % 3;
	int split = 0;
	for (int i = 0; i < number; i++) {
		int posy = 13 - (i % 5);
		int posx = split;
		Vehiculo temp(posx, posy, i % 5);
		vehiculos[i] = temp;
		split += 2;
	}
}
void setVehiculos::draw() {
	for (int i = 0; i < number; i++) {
		vehiculos[i].draw();
	}
}

Tronco::Tronco(int x, int y, int type) {
	int coordsMultiplier = round(W.GetHeight() / 16);
	int sizeMultiplier = 2;
	timeCounter = 0;
	coords.first = x * coordsMultiplier;
	coords.second = y * coordsMultiplier;

	switch (type) {
	//grande
	case 2:
			size.first = 177 * sizeMultiplier;
			size.second = 21 * sizeMultiplier;
			speed = 1;
			timeInterval = 15;
			sp.objectID = ObjectID::TRUNKL;
			break;
	//mediano
	case 1:
			size.first = 116 * sizeMultiplier;
			size.second = 21 * sizeMultiplier;
			speed = 1;
			timeInterval = 17;
			sp.objectID = ObjectID::TRUNKM;
			break;

	//pequeño
	case 0:
			size.first = 84 * sizeMultiplier;
			size.second = 21 * sizeMultiplier;
			speed = 1;
			timeInterval = 20;
			sp.objectID = ObjectID::TRUNKS;
			break;
	}
	maxTimeCounter = timeInterval;
	sp.transform = { coords.first, coords.second, size.first, size.second };
}
void Tronco::SetSpeedModifier(int speedModifier) {
	speed = speedModifier;
}

std::pair <bool, int> Tronco::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	//colisión
	std::pair <bool, int> temp;
	temp.second = 0;
	if (coords.second == Pcoords.second && Pcoords.first + Psize.first / 2 >= coords.first && Pcoords.first + Psize.first / 2 <= coords.first + size.first) {
		temp.first = true;
		if (moveFrog)temp.second = speed;
		return temp;
	}
	else {
		temp.first = false;
	}
	return temp;
}

std::pair<int, int> Tronco::getCoords() {
	return coords;
}
std::pair<int, int> Tronco::getSize() {
	return size;
}

void Tronco::update() {
	
	timeCounter = SDL_GetTicks();
	if (timeCounter >= maxTimeCounter && timeCounter <= maxTimeCounter + timeInterval) {
		moveFrog = true;
		coords.first += speed;
		
		if (coords.first > W.GetWidth()) {
			coords.first = -size.first;
		}
		maxTimeCounter += timeInterval;
	}
	else if (timeCounter > maxTimeCounter + timeInterval) {
		maxTimeCounter = timeCounter + timeInterval;
		moveFrog = false;
	}
	else moveFrog = false;
}
void Tronco::draw() {
	
	sp.transform = { coords.first, coords.second, size.first, size.second };
	sp.Draw();
}

setTroncos::setTroncos() {
	number = 9;
	
	//troncos de la fila 
	troncos[0] = Tronco(1, 6, 0);
	troncos[1] = Tronco(7, 6, 0);
	troncos[2] = Tronco(13, 6, 0);
	troncos[3] = Tronco(19, 6, 0);
	troncos[4] = Tronco(3, 5, 2);
	troncos[5] = Tronco(18, 5, 2);
	troncos[6] = Tronco(4, 3, 1);
	troncos[7] = Tronco(13, 3, 1);
	troncos[8] = Tronco(22, 3, 1);
}
void setTroncos::SetSpeedModifier(int speedModifier) {
	for (int i = 0; i < number; i++) {
		troncos[i].SetSpeedModifier(speedModifier);
	}
}
void setTroncos::update() {
	for (int i = 0; i < number; i++) {
		troncos[i].update();
	}
}

std::pair <bool, int> setTroncos::collisions(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	std::pair <bool, int> temp;
	for (int i = 0; i < number; i++) {
		temp = troncos[i].collision(Pcoords, Psize);
		if (temp.first){
			return temp;
		}
	}
	temp.first = false;
	temp.second = 0;
	return temp;
}

void setTroncos::draw() {
	for (int i = 0; i < number; i++) {
		troncos[i].draw();
	}
}

Tortuga::Tortuga(int x, int type, bool disappear) {
	int coordsMultiplier = round(W.GetHeight() / 16);
	int sizeMultiplier = 2;
	size.first = 31 * sizeMultiplier;
	size.second = 22 * sizeMultiplier;
	coords.first = x * coordsMultiplier;
	speed = -1;
	submerge = disappear;
	visible = true;
	stateIntervalSubmerge = 300;
	stateIntervalEmerge = 80;
	stateCounter = 0;
	maxStateCounter = stateIntervalSubmerge;
	switch (type) {
		//cadenas de 3
	case 0:
		coords.second = 7 * coordsMultiplier;
		timeInterval = 22;
		break;
		//cadenas de 2
	case 1:
		coords.second = 4 * coordsMultiplier;
		timeInterval = 17;
		break;
	default:
		break;
	}

	timeCounter = 0;
	maxTimeCounter = timeInterval;
	sp.objectID = ObjectID::TURTLE1;
	
	sp.transform = { coords.first, coords.second, size.first, size.second };
}
void Tortuga::SetSpeedModifier(int speedModifier) {
	speed = -speedModifier;
}
std::pair <bool, int> Tortuga::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	//colisión
	std::pair <bool, int> temp;
	temp.second = 0;

	if (coords.second == Pcoords.second && Pcoords.first + Psize.first / 2 >= coords.first && Pcoords.first + Psize.first / 2 <= coords.first + size.first && visible) {
		temp.first = true;
		if (moveFrog)temp.second = speed;
		return temp;
	}
	else {
		temp.first = false;
	}
	return temp;
}

std::pair<int, int> Tortuga::getCoords() {
	return coords;
}
std::pair<int, int> Tortuga::getSize() {
	return size;
}

void Tortuga::update() {
	timeCounter = SDL_GetTicks();
	if (timeCounter >= maxTimeCounter && timeCounter <= maxTimeCounter + timeInterval) {
		moveFrog = true;
		coords.first += speed;

		if (coords.first < -size.first) {
			coords.first = W.GetWidth();
		}

		
		//submerge switch
		if (timeCounter > maxStateCounter && submerge) {
			stateCounter += 1;

			//submerge sprites
			if (stateCounter > maxStateCounter - stateIntervalSubmerge / 5) {
				sp.objectID = sp.objectID = ObjectID::TURTLE2;
			}
			else {
				sp.objectID = sp.objectID = ObjectID::TURTLE1;
			}

			if (visible && stateCounter >= maxStateCounter) {
				visible = false;
				maxStateCounter = stateIntervalEmerge;
				stateCounter = 0;
			}
			else if (visible == false && stateCounter >= maxStateCounter / 2) {
				visible = true;
				maxStateCounter = stateIntervalSubmerge;
				stateCounter = 0;
			}
			
		}
		maxTimeCounter += timeInterval;
	}
	else if (timeCounter > maxTimeCounter + timeInterval) {
		maxTimeCounter = timeCounter + timeInterval;
		moveFrog = false;
	}
	else moveFrog = false;
}
void Tortuga::draw() {

	sp.transform = { coords.first, coords.second, size.first, size.second };
	if (visible) {
		sp.Draw();
	}
}

setTortugas::setTortugas() {
	number = 20;

	//troncos de la fila 
	tortugas[0] = Tortuga(0, 0, true);
	tortugas[1] = Tortuga(1, 0, true);
	tortugas[2] = Tortuga(2, 0, true);

	tortugas[3] = Tortuga(5, 0, false);
	tortugas[4] = Tortuga(6, 0, false);
	tortugas[5] = Tortuga(7, 0, false);

	tortugas[6] = Tortuga(10, 0, true);
	tortugas[7] = Tortuga(11, 0, true);
	tortugas[8] = Tortuga(12, 0, true);

	tortugas[9] = Tortuga(15, 0, false);
	tortugas[10] = Tortuga(16, 0, false);
	tortugas[11] = Tortuga(17, 0, false);

	tortugas[12] = Tortuga(0, 1, true);
	tortugas[13] = Tortuga(1, 1, true);

	tortugas[14] = Tortuga(6, 1, false);
	tortugas[15] = Tortuga(7, 1, false);

	tortugas[16] = Tortuga(12, 1, true);
	tortugas[17] = Tortuga(13, 1, true);

	tortugas[18] = Tortuga(18, 1, false);
	tortugas[19] = Tortuga(19, 1, false);
}

void setTortugas::SetSpeedModifier(int speedModifier) {
	for (int i = 0; i < number; i++) {
		tortugas[i].SetSpeedModifier(speedModifier);
	}
}

void setTortugas::update() {
	for (int i = 0; i < number; i++) {
		tortugas[i].update();
	}
}

std::pair <bool, int> setTortugas::collisions(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	std::pair <bool, int> temp;
	for (int i = 0; i < number; i++) {
		temp = tortugas[i].collision(Pcoords, Psize);
		if (temp.first) {
			return temp;
		}
	}
	temp.first = false;
	temp.second = 0;
	return temp;
}

void setTortugas::draw() {
	for (int i = 0; i < number; i++) {
		tortugas[i].draw();
	}
}

Insecto::Insecto(int x) {
	int coordsMultiplier = round(W.GetHeight() / 16);
	int sizeMultiplier = 2;

	coords.first = x;
	coords.second = 2 * coordsMultiplier;
	size.first = 31 * sizeMultiplier;
	size.second = 22 * sizeMultiplier;
	insectActive = false;
	frogs = false;
	spInsect.objectID = ObjectID::INSECT;
	spFrog.objectID = ObjectID::FROG;
	spInsect.transform = { coords.first, coords.second, size.first, size.second };
	spFrog.transform = { coords.first, coords.second, size.first, size.second };
}

std::pair<bool, bool> Insecto::collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize) {
	//colisión
	std::pair<bool, bool> temp; //1r bool si la rana ha llegado al final, segundo bool si ha sido con insecto
	if (!frogs) {
		if (coords.second == Pcoords.second && Pcoords.first + Psize.first / 2 >= coords.first && Pcoords.first + Psize.first / 2 <= coords.first + size.first) {
			temp.first = true;
			if (insectActive) {
				temp.second = true;
				insectActive = false;
			}
			else temp.second = false;
			frogs = true;
			return temp;
		}
	}
	temp.first = false;
	temp.second = false;
	return temp;
}

std::pair<int, int> Insecto::getCoords() {
	return coords;
}
std::pair<int, int> Insecto::getSize() {
	return size;
}

void Insecto::update(bool active) {
	if (!frogs) {
		if (active) {
			insectActive = true;
		}
		else insectActive = false;
	}
}
void Insecto::draw() {
	if (frogs) {
		spFrog.Draw();
	}
	else if (insectActive) {
		spInsect.transform = { coords.first, coords.second, size.first, size.second };
		spInsect.Draw();
	}
}

setInsectos::setInsectos() {
	number = 5;
	timeCounter = 0;
	timeInterval = 1000; 
	maxTimeCounter = timeInterval;
	switchCounter = 0;
	maxSwitchCounter = 15;
	active = false;
	insectos[0] = Insecto(40) ;
	insectos[1] = Insecto(260);
	insectos[2] = Insecto(475);
	insectos[3] = Insecto(690);
	insectos[4] = Insecto(910);
}

void setInsectos::update() {
	timeCounter = SDL_GetTicks();
	if (timeCounter >= maxTimeCounter && timeCounter <= maxTimeCounter + timeInterval) {
		switchCounter += 1;
		if (!active && switchCounter > maxSwitchCounter) {
			active = true;
			int randomInsect = rand() % 5;
			insectos[randomInsect].update(true);
			switchCounter = 0;
		}
		else if (active && switchCounter > maxSwitchCounter) {
			active = false;
			for (int i = 0; i < number; i++) {
				insectos[i].update(false);
			}
			switchCounter = 0;
		}
		
		maxTimeCounter += timeInterval;
	}
	else if (timeCounter >= maxTimeCounter + timeInterval) {
		maxTimeCounter = timeCounter + timeInterval;
	}
	
}

bool setInsectos::collisions(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize, int &score, int &totalfrogs, int timeRemaining) {
	
	for (int i = 0; i < number; i++) {
		std::pair<bool, bool> temp = (insectos[i].collision(Pcoords, Psize)); //recoge ambos datos de la colision original
		if (temp.first) {
			if (temp.second) score += 200;
			score += round(timeRemaining * 10)+50;
			++totalfrogs;
			if (totalfrogs == 5) score += 1000;
			return true;
		}
	}
	return false;
}

void setInsectos::reset() {
	active = false;
	insectos[0] = Insecto(40);
	insectos[1] = Insecto(260);
	insectos[2] = Insecto(475);
	insectos[3] = Insecto(690);
	insectos[4] = Insecto(910);
}

void setInsectos::draw() {
	for (int i = 0; i < number; i++) {
		insectos[i].draw();
	}
}