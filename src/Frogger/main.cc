#include "GameEngine.hh"
#include <../inc/XML/rapidxml_utils.hpp>
#include <sstream>

// Game constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

using namespace std;
using namespace rapidxml;
int main(int argc, char* args[]) {
	cout << "Parsing levels . . . " << endl;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile("DifficultyParse.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("levels");
	for (xml_node<> * easy_node = root_node->first_node("easy"); easy_node; easy_node = easy_node->next_sibling())
	{
		printf("I have visited %s in %s. ",
			easy_node->first_attribute("name")->value(),
			easy_node->first_attribute("location")->value());
	}
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Frogger");

	return 0;
}