#pragma once
#include <fstream>
#include <sstream>
#include "Logger.hh"
#include "Resource.hh"
#include <../inc/XML/rapidxml_utils.hpp>
//#include <XML/rapidxml_utils.hpp>

using namespace Logger;

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