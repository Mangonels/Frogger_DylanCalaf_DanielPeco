#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Vehiculo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	Sprite sp1;
	//VehiclesID tipo;
public:
	Vehiculo();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void draw();
	//VehiclesID getType();
};

class Tronco {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	Sprite sp2;
public:
	Tronco();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void draw();
};

class Tortuga {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	Tortuga();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
};

class Nutria {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	Nutria();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
};

class Cocodrilo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	CocodriloID tipo;
public:
	Cocodrilo();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	//std::pair<int, int> getType();
};

class Serpiente {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	Serpiente();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
};

class Insecto {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	Insecto();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
};

class LadyFrog {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	LadyFrog();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
};
