#include "GameEngine.hh"
#include "IOManager.hh"

// Game constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

using namespace std;

int main(int argc, char* args[]) {
	
   IOManager::XMLParser("xml/Difficulties.xml", "medium");

	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Frogger");

	return 0;
}