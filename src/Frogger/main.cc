#include "GameEngine.hh"
#include <../inc/XML/rapidxml_utils.hpp>
#include <sstream>
#include <fstream>

// Game constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main(int argc, char* args[]) {
	
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Frogger");
	return 0;
}