/*
 * Config.cpp
 *
 *  Created on: 6/9/2014
 *      Author: pablo_000
 */

#include "Config.h"
#include "../src/Constantes.h"
#include "Parser.h"

Config::Config(string dirArchivoConfiguracion) {
	this->dirArchivoConfiguracion = dirArchivoConfiguracion;
	this->unParser = NULL;
}

void Config::reset() {

}

void Config::crearObjetos(){
	Parser *unParser = new Parser("prueba.json");
	this->unParser = unParser;
}

Pantalla* Config::getPantalla() {
	return this->unParser->getPantalla();
}

vector<Personaje*>* Config::getPersonajes() {
	return this->unParser->getPersona();
}

vector<ObjetoMapa*>* Config::getObjetos() {
	return this->unParser->getObjetos();
}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

