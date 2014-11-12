#include "ElementosJuego.h"

unsigned int ElementosJuego::getID(){
	return this->ID;
}

void ElementosJuego::setID(unsigned int ID){
	this->ID = ID;
}

/*
 * Getter y setter para la posicion
 */
Pos ElementosJuego::getPos() {
	return pos;
}

void ElementosJuego::setPos(Pos posicion) {
	pos = posicion;
}

ElementosJuego::~ElementosJuego() {
}
