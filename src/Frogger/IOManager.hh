#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <../inc/XML/rapidxml_utils.hpp>
//#include <XML/rapidxml_utils.hpp>
using namespace Logger;

namespace IOManager {

	void TestXML(std::string &&filename) { //pasas un string.
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename)); //carreguem filename a un a variable file de XML     ¿¿QUE HACE RESOURCE_FILE?? PLZ ANSWER>
		rapidxml::xml_document<> doc; //creem un espai de memoria per a un document xml
		doc.parse<0>(xmlFile.data()); //parsejem doc i hi asignem el contingut (data()) de xmlFile
		rapidxml::xml_node<> *root_node = doc.first_node("levels"); //root node contindrá el primer node, que será <levels>
		for (rapidxml::xml_node<> * node = root_node->first_node("node"); node; node = node->next_sibling()) {
			Println("Node: ",
				node->first_attribute("att1")->value(),
				" - ",
				node->first_attribute("att2")->value());
		}
	}

/*	void xmlReader(std::string &&level) {

		rapidxml::file<> xmlFile("difficulties.xml");
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("levels");
		for (rapidxml::xml_node<> * node = root_node->first_node(level); node; node = node->next_sibling()) {
			Println("Node: ", node->first_attribute()->value());
		}
	}*/


	// Loader function that takes level info for a grid
	std::vector<std::vector<ObjectID>> LoadLevel(std::string &&filename, int &rows, int &cols) {
		std::ifstream fileData(RESOURCE_FILE(filename));
		ASSERT(fileData.good());
		std::vector<std::vector<ObjectID>> lvlData;
		std::string line;
		while (std::getline(fileData, line)) {
			std::istringstream strData(std::move(line));
			lvlData.emplace_back(std::istream_iterator<ObjectID>(std::move(strData)), std::istream_iterator<ObjectID>());
		}
		rows = int(lvlData.size()); cols = int(lvlData[0].size());
		fileData.close();
#pragma region DEBUG_DATA
		Println("Level: ", filename);
		for (auto &r : lvlData) {
			for (auto &c : r) Print(c, ' ');
			Endln();
		}
#pragma endregion
		return std::move(lvlData);
	}

}