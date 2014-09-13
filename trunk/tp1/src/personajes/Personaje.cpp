#include "Personaje.h"

Personaje::Personaje(Pos posicion) {
	this->pos = posicion;
}

// getter y setter de la posicion
void Personaje::setPosicion(Pos posicion) {
	this->pos = posicion;
}
Pos Personaje::getPosicion(){
	return this->pos;
}

// devuelve verdadero si esta en esa posicion
bool Personaje::estaEnPos(Pos posicion) {
	return this->pos.esIgual(posicion);
}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

