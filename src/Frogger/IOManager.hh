#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <../inc/XML/rapidxml_utils.hpp>

using namespace Logger;

namespace IOManager {

	static void XMLParser(std::string &&filename, std::string &&level, int &PHealth, int &GTime, int &GInitSpeed) {
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename)); //carreguem filename a un a variable file de XML
		rapidxml::xml_document<> doc; //creem un espai de memoria per a un document xml
		try {
			doc.parse<0>(xmlFile.data()); //parsejem doc i hi asignem el contingut (data()) de xmlFile
		}
		catch (rapidxml::parse_error err) {
			std::cout << err.what() << std::endl /*<< err.where() << std::endl*/;
			system("pause");
		}
		rapidxml::xml_node<> *root_node = doc.first_node("levels"); //root node contindrá el primer node, que será <levels>

		rapidxml::xml_node<> *difficulty_node = root_node->first_node(level.c_str()); //basicament aqui estem escalant de node en node, fins arrivar al nivell de l'arbre que volem.

		rapidxml::xml_node<> *healthAttr = difficulty_node->first_node("PHealth"); //busquem el node PHealth que conté la vida del frogger
		PHealth = std::stoi(healthAttr->value());//Canviem el tipus de la variable obtinguda (un string) a int, de manera que ens sera mes util

		rapidxml::xml_node<> *timeAttr = difficulty_node->first_node("GTime"); //mateixa operacio
		GTime = std::stoi(timeAttr->value());

		rapidxml::xml_node<> *initspeedAttr = difficulty_node->first_node("GInitSpeed"); //same
		GInitSpeed = std::stoi(initspeedAttr->value());
	}

/*Alternatives amb iteradors: */

	static void XMLParserBasic(std::string &&filename, std::string &&level) {
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename)); //carreguem filename a un a variable file de XML
		rapidxml::xml_document<> doc; //creem un espai de memoria per a un document xml
		try {
			doc.parse<0>(xmlFile.data()); //parsejem doc i hi asignem el contingut (data()) de xmlFile
		}
		catch (rapidxml::parse_error err) {
			std::cout << err.what() << std::endl /*<< err.where() << std::endl*/;
			system("pause");
		}
		rapidxml::xml_node<> *root_node = doc.first_node("levels"); //root node contindrá el primer node, que será <levels>
			rapidxml::xml_node<> *difficulty_node = root_node->first_node(level.c_str()); //basicament aqui estem escalant de node en node, fins arrivar al nivell de l'arbre que volem.

		for (rapidxml::xml_node<> *attr = difficulty_node->first_node(); attr != difficulty_node->last_node(); attr = attr->next_sibling()) {
			Println(
				attr->name(),
				"Value: ",
				attr->value());
	}
/*
		for (rapidxml::xml_node<> *difficulty_node = root_node->first_node("easy"); difficulty_node; difficulty_node = difficulty_node->next_sibling()) {
			Println("Node: ",
				difficulty_node->first_attribute("time")->value(),
				" - ",
				difficulty_node->first_attribute("lives")->value(),
				" - ",
				difficulty_node->first_attribute("initSpeed")->value());
		}
*/
	}
/*
	void xmlReader(std::string &&level) {

		rapidxml::file<> xmlFile("difficulties.xml");
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("levels");
		for (rapidxml::xml_node<> * node = root_node->first_node(level); node; node = node->next_sibling()) {
			Println("Node: ", node->first_attribute()->value());
		}
	}
*/
/*
	// Loader function that takes level info for a grid
    static std::vector<std::vector<ObjectID>> LoadLevel(std::string &&filename, int &rows, int &cols) {
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

*/

}