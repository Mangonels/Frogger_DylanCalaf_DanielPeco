#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Vehiculo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	Sprite sp;
	//VehiclesID tipo;
public:
	Vehiculo() {};
	Vehiculo(int x, int y);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	bool collision(const std::pair<int, int>, const std::pair<int, int>);
	void draw();
	//VehiclesID getType();
};

class setVehiculos {
	int number;
	Vehiculo vehiculos[10];
public:
	setVehiculos();
	bool collisions(const std::pair<int, int>, const std::pair<int, int>);
	void draw();
};

class Tronco {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	Sprite sp;
public:
	Tronco() {};
	Tronco(int x, int y);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	bool collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize);
	void draw();
};

class setTroncos {
	int number;
	Tronco troncos[10];
public:
	setTroncos();
	bool collisions(const std::pair<int, int>, const std::pair<int, int>);
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
