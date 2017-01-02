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

/*	void inputOutput() { //Hace las 2 cosas a la vez
		char input[100];
		strcpy(input, "wololo"); //Insertar la cadena de caracteres en el array de chars.

		std::fstream file("ranking.bin", ios::binary | ios::in | ios::out | ios::trunc); //trunc -> se carga el contenido del archivo para reusarlo.

		if (!file.is_open()) std::cout << "Error while opening the file" << std::endl;
		else
		{
			int length = strlen(input);
			for (int counter = 0; counter <= length; counter++)
			{
				file.put(input[counter]);
			}

			file.seekg(0);
			char ch;
			while (file.good())
			{
				file.get(ch);
				std::cout << ch;
			}
			*/
	}
}



namespace binaryIO {

	static void bFileScoreInsert(std::string player, int score) //Inserta puntuación en el archivo "scores.dat"
	{
		string strScore = to_string(score);
		string input = player + " " + strScore;

		std::fstream outfile("scores.dat", ios::out | ios::binary);    //preparamos el archivo scores.dat (el cual se generará si no existe) y determinamos que será un archivo de salida(ios::out) en binario(ios::binary).
		outfile.write(reinterpret_cast<char *>(&input), input.size()); //write(s,n) 
																	   //s = Puntero a un array que tiene como minimo n caracteres. "reinterpret_cast<char *>", delante de la dirección de memoria del input, transforma el contenido de la dirección de memoria de input a una cadena de caracteres.
																	   //n = Numero de caracteres a insertar (En este caso tantos como el tamaño de input)
		outfile.close();
	}

	static void bFileScoresRead() //Lee todas las puntuaciones del archivo "scores.dat"
	{
		string output = "";

		std::fstream infile("scores.dat", ios::in | ios::binary);
		infile.read(reinterpret_cast<char *>(&output), output.size());

		infile.close();

		cout << output << endl;
	}
	//linea random adicional
}
