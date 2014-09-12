#include "Personaje.h"

Personaje::Personaje(Pos posicion) {
	this->pos = posicion;
}

// getter y setter de la posicion
void setPosicion(Pos posicion) {
	this->pos = posicion;
}
Pos getPosicion(){
	return this->pos;
}

// devuelve verdadero si esta en esa posicion
bool estaEnPos(Pos posicion) {
	return this->pos.esIgual(posicion);
}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

