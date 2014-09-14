/*
 * Paralelogramo.cpp
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#include <objetos/Paralelogramo.h>

Paralelogramo::Paralelogramo(Pos posicion, int base, int altura, int alfa, int rotacion,std::string color,int masa,bool estatico) {
	this->base = base;
	this->altura = altura;
	this->alfa = alfa;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

std::vector<Pos>* Paralelogramo::getContorno() {
	return nullptr;
}

Paralelogramo::~Paralelogramo() {
	// TODO Auto-generated destructor stub
}

