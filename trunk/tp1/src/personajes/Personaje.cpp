#include "Personaje.h"

Personaje::Personaje(Pos* posicion) {
	pos = posicion;
	rot = 0;
	linkAMundo = nullptr;
	ancho = 60;
	alto = 80;
	rectanguloPersonaje = new Rectangulo(false, "#00F0A0", pos, 0, 80, alto, ancho);
}

// getter de dimensiones
int Personaje::getAlto(){
	return alto;
}
int Personaje::getAncho(){
	return ancho;
}

// getter y setter de la posicion
void Personaje::setPosicion(Pos* posicion) {
	pos = posicion;
}
Pos* Personaje::getPosicion(){
	return pos;
}

std::vector<Pos*>* Personaje::getContorno() {
	return rectanguloPersonaje->getContorno();
}
// devuelve verdadero si esta en esa posicion
bool Personaje::estaEnPos(Pos* posicion) {
	return pos->esIgual(posicion);
}

Rectangulo* Personaje::getRectangulo() {
	return rectanguloPersonaje;
}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

// getter y setter de link a mundo
void Personaje::setLinkAMundo(b2Body* link){
	linkAMundo = link;
}

b2Body* Personaje::getLinkAMundo(){
	return linkAMundo;
}
