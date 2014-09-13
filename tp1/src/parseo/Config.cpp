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
	this->objetos = new vector<ObjetoMapa>();
	this->personajes = new vector<Personaje>();
}

void Config::reset() {

}

void Config::CrearObjetos(){
	Parser *unParser = new Parser("prueba.json");
}

Pantalla* Config::getPantalla() {
	/*Pantalla *p = new Pantalla();
	vector<int> dim = pantalla->getDimensionesPx();
	p->setDimensionesPx(dim[0], dim[1]);
	dim = pantalla->getDimensiones();
	p->setDimensiones(dim[0], dim[1]);
	p->setFondo(pantalla->getFondo());
	return p;*/
}

vector<Personaje>* Config::getPersonajes() {
}

vector<ObjetoMapa>* Config::getObjetos() {
}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

