#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include "Window.hh"
#include <../inc/XML/rapidxml_utils.hpp>
#include <SDL/SDL.h>
#include <string>
#include "RankingScene.hh"
using namespace Logger;
using namespace std;

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
		rapidxml::xml_node<> *root_node = doc.first_node("levels"); //root node contindr� el primer node, que ser� <levels>

		rapidxml::xml_node<> *difficulty_node = root_node->first_node(level.c_str()); //basicament aqui estem escalant de node en node, fins arrivar al nivell de l'arbre que volem.

		rapidxml::xml_node<> *healthAttr = difficulty_node->first_node("PHealth"); //busquem el node PHealth que cont� la vida del frogger
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
		rapidxml::xml_node<> *root_node = doc.first_node("levels"); //root node contindr� el primer node, que ser� <levels>
		rapidxml::xml_node<> *difficulty_node = root_node->first_node(level.c_str()); //basicament aqui estem escalant de node en node, fins arrivar al nivell de l'arbre que volem.

		for (rapidxml::xml_node<> *attr = difficulty_node->first_node(); attr != difficulty_node->last_node(); attr = attr->next_sibling()) {
			Println(
				attr->name(),
				"Value: ",
				attr->value());
		}
	}
}
