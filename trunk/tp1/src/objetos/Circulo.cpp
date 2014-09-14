/*
 * Circulo.cpp
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#include <objetos/Circulo.h>

Circulo::Circulo(Pos posicion, int diametro,int rotacion,std::string color,int masa,bool estatico){
	this->diametro = diametro;
	this->initialice(estatico, color, posicion, rotacion, masa);

}

std::vector<Pos>* Circulo::getContorno() {
	return nullptr;
}


Circulo::~Circulo() {
	// TODO Auto-generated destructor stub
}

