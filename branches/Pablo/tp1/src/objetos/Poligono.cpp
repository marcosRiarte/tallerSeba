/*
 * Poligono.cpp
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#include "Poligono.h"

Poligono::Poligono(Pos posicion, int lados, int escala, int rotacion,std::string color,int masa,bool estatico) {
	this->lados = lados;
	this->escala = escala;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

std::vector<Pos>* Poligono::getContorno() {
	return nullptr;
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

