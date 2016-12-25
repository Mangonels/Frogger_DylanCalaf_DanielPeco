#pragma once
#include "Sprite.hh"
#include "InputManager.hh"

class Vehiculo {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	Sprite sp;
	int speed;
	int timeCounter;
	int maxTimeCounter;
	int timeInterval;
	//VehiclesID tipo;
public:
	Vehiculo() {};
	Vehiculo(int x, int y, int type);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void update();
	void SetSpeedModifier(int speedModifier);
	bool collision(const std::pair<int, int>, const std::pair<int, int>);
	void draw();
	//VehiclesID getType();
};

class setVehiculos {
	int number;
	Vehiculo vehiculos[10];
public:
	setVehiculos();
	void update();
	void SetSpeedModifier(int speedModifier);
	bool collisions(const std::pair<int, int>, const std::pair<int, int>);
	void NewLevel(int level);
	void draw();
};

class Tronco {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	int speed;
	int timeCounter;
	int maxTimeCounter;
	int timeInterval;
	bool moveFrog;
	Sprite sp;
public:
	Tronco() {};
	Tronco(int x, int y, int type);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void update();
	void SetSpeedModifier(int speedModifier);
	std::pair <bool, int> collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize);
	void draw();
};

class setTroncos {
	int number;
	Tronco troncos[9];
public:
	setTroncos();
	void update();
	void SetSpeedModifier(int speedModifier);
	std::pair <bool, int> collisions(const std::pair<int, int>, const std::pair<int, int>);
	void draw();
};

class Tortuga {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	int speed;
	int timeCounter;
	int maxTimeCounter;
	int timeInterval;

	int maxStateCounter;
	int stateIntervalSubmerge;
	int stateIntervalEmerge;
	bool moveFrog;
	bool submerge;
	bool visible;
	Sprite sp;
public:
	Tortuga() {};
	Tortuga(int x, int type, bool disappear);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void update();
	void SetSpeedModifier(int speedModifier);
	std::pair <bool, int> collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize);
	void draw();
};

class setTortugas {
	int number;
	Tortuga tortugas[20];
public:
	setTortugas();
	void update();
	void SetSpeedModifier(int speedModifier);
	std::pair <bool, int> collisions(const std::pair<int, int>, const std::pair<int, int>);
	void draw();
};

class Insecto {
	std::pair<int, int> coords;
	std::pair<int, int> size;
	bool insectActive;
	bool frogs;
	Sprite spInsect;
	Sprite spFrog;
public:
	Insecto() {};
	Insecto(int x);
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
	void update(bool active);
	std::pair<bool, bool> collision(const std::pair<int, int> Pcoords, const std::pair<int, int> Psize);
	void draw();
};

class setInsectos {
	int number;
	Insecto insectos[5];
	int totalGoals;
	int timeCounter;
	int maxTimeCounter;
	int timeInterval;
	bool active;
public:
	setInsectos();
	void update();
	bool collisions(const std::pair<int, int>, const std::pair<int, int>, int &score, int &totalfrogs);
	void reset();
	void draw();
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

class LadyFrog {
	std::pair<int, int> coords;
	std::pair<int, int> size;
public:
	LadyFrog();
	std::pair<int, int> getCoords();
	std::pair<int, int> getSize();
};
