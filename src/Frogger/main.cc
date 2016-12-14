#include "GameEngine.hh"
#include "IOManager.hh"
#include <string>

// Game constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

using namespace std;

int main(int argc, char* args[]) {

	string difficulty{ "hard" };

	xmlReader(difficulty);

	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Frogger");

	return 0;
}