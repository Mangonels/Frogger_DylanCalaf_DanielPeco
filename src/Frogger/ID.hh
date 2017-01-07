#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	BG_00, BG_01, // Background IDs
	FROG,//frogger IDs
	VEHICLE1, VEHICLE2, VEHICLE3, VEHICLE4, VEHICLE5,
	TRUNKL, TRUNKM, TRUNKS,
	TURTLE1, TURTLE2, INSECT
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator >> (std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };


// Enum ID used to store each true type font for text rendering
enum class FontID : int {
	ARIAL,
	FACTORY,
	RAKOON,
	MAX
};