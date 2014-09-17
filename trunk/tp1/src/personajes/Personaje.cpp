#include "Personaje.h"

Personaje::Personaje(Pos* posicion,float rotacion) {
	pos = posicion;
	rot = rotacion;
}

// getter y setter de la posicion
void Personaje::setPosicion(Pos* posicion) {
	pos = posicion;
}
Pos* Personaje::getPosicion(){
	return pos;
}

float Personaje::getRotacion(){
	return rot;
}

// devuelve verdadero si esta en esa posicion
bool Personaje::estaEnPos(Pos* posicion) {
	return pos->esIgual(posicion);
}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

