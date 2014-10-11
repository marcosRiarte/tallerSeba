#include "ElementosJuego.h"
#include "../Constantes.h"
#include <math.h>
#include <exception>

/*
 * Devuelve la densidad del elemento
 */
float ElementosJuego::getDensidad() {
	return (masa / this->getArea());
}

/*
 * Getter y setter para la posicion
 */
Pos* ElementosJuego::getPos() {
	return pos;
}
void ElementosJuego::setPos(Pos* posicion) {
	pos = posicion;
}

/*
 * Getter y setter para el angulo de rotacion
 */
float ElementosJuego::getRotacion() {
	return rot;
}
void ElementosJuego::setRotacion(float rotacion) {
	rot = rotacion;
}

/*
 * Getter y setter para el link al mundo
 */
b2Body* ElementosJuego::getLinkAMundo() {
	return linkAMundo;
}
void ElementosJuego::setLinkAMundo(b2Body* link) {
	linkAMundo = link;
}

ElementosJuego::~ElementosJuego() {
	delete pos;
}
