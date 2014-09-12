/*
 * Config.cpp
 *
 *  Created on: 6/9/2014
 *      Author: pablo_000
 */

#include "Config.h"


Config::Config(string dirArchivoConfiguracion) {
	this->dirArchivoConfiguracion = dirArchivoConfiguracion;
	this->pantalla = NULL;
	this->objetos = new vector<ObjetoMapa>();
	this->personajes = new vector<Personaje>();
}

void Config::reset() {
	pantalla = new Pantalla(480, 640, 70, 100, "SDL_ImageTest.jpg");
}

Pantalla* Config::getPantalla() {
	return pantalla;
}

vector<Personaje>* Config::getPersonajes() {
}

vector<ObjetoMapa>* Config::getObjetos() {
}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

