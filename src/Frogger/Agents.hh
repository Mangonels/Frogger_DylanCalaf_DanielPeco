#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Vehiculo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	VehiclesID tipo;
public:
	void getCoords() {}
	void getSize() {}
	void getType() {}
};

class Tronco {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	void getCoords() {}
	void getSize() {}
};

class Tortuga {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	void getCoords() {}
	void getSize() {}
};

class Nutria {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	void getCoords() {}
	void getSize() {}
};

class Cocodrilo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	CocodriloID tipo;
public:
	void getCoords() {}
	void getSize() {}
	void getType() {}
};

class Serpiente {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	void getCoords() {}
	void getSize() {}
};

class Insecto {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	void getCoords() {}
	void getSize() {}
};

class LadyFrog {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	void getCoords() {}
	void getSize() {}
};