/*
 * Trapecio.cpp
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#include "Trapecio.h"

Trapecio::Trapecio(Pos posicion, int base, int altura, int alfa, int beta,int rotacion,std::string color,int masa,bool estatico){
	this->base = base;
	this->altura = altura;
	this->alfa = alfa;
	this->beta = beta;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

std::vector<Pos>* Trapecio::getContorno() {
	return nullptr;
}

Trapecio::~Trapecio() {
	// TODO Auto-generated destructor stub
}

