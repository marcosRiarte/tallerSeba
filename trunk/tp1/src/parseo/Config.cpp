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
	this->pantalla = NULL;
	this->objetos = new vector<ObjetoMapa*>();
	this->personajes = new vector<Personaje*>();
}

void Config::reset() {

}

void Config::CrearObjetos(){
	Parser *unParser = new Parser("prueba.json");
}

Pantalla* Config::getPantalla() {
	return pantalla;
}

vector<Personaje*>* Config::getPersonajes() {
	return nullptr;
}

vector<ObjetoMapa*>* Config::getObjetos() {
	return nullptr;
}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

