/*
 * Rectangulo.cpp
 *
 *  Created on: 9/9/2014
 *      Author: pablo_000
 */

#include "Rectangulo.h"

Rectangulo::Rectangulo(bool esEstatico, Color color, Pos pos_cm, int rotacion,
		float masa, int alto, int ancho) {
	if ((alto <= 0) || (ancho <= 0))
		throw new std::exception();
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

