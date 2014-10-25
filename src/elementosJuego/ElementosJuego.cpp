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
 * Devuelve la friccion del elemento
 */
float ElementosJuego::getFriccion() {
	return friccion;
}

/*
 * Devuelve un vector de Posiciones que define el contorno de la figura
 */
std::vector<Pos> ElementosJuego::getContorno() {
	return vertices;
}

float ElementosJuego::getArea(){
	return area;
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
}
