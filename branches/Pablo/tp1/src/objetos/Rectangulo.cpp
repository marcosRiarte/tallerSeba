/*
 * Rectangulo.cpp
 *
 *  Created on: 9/9/2014
 *      Author: pablo_000
 */

#include "Rectangulo.h"

Rectangulo::Rectangulo(bool esEstatico, std::string color, Pos pos_cm, int rotacion,
		int masa, int alto, int ancho) {

	this->alto = alto;
	this->ancho = ancho;
	this->initialice(esEstatico, color, pos_cm, rotacion, masa);
}

std::vector<Pos>* Rectangulo::getContorno() {
	return nullptr;
}

Rectangulo::~Rectangulo() {
	// TODO Auto-generated destructor stub
}

