#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Vehiculo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	VehiclesID tipo;
public:
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	VehiclesID getType();
};

class Tronco {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
};

class Tortuga {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
};

class Nutria {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
};

class Cocodrilo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	CocodriloID tipo;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
	std::pair<int, int> getType() {}
};

class Serpiente {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
};

class Insecto {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
};

class LadyFrog {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	std::pair<int, int> getCoords() {}
	std::pair<int, int> getSize() {}
};