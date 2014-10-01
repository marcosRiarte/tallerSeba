#include "Personaje.h"

Personaje::Personaje(Pos* posicion) {
	pos = posicion;
	rot = 0;
	linkAMundo = nullptr;
	ancho = 16;
	alto = 24;
	this->estado= "QuietoIzq";

	/* Esto hace que explote, por lo que se deja comentado, revisar esta logica TODO
	estado->perfil = E_PERFIL::IZQUIERDA;
	estado->accion = E_ACCION::QUIETO;
	*/
	rectanguloPersonaje = new Rectangulo(false, "#00F0A0", pos, 0, 80, alto, ancho); // Solo para pruebas...

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
	rectanguloPersonaje->setPos(posicion);
}
Pos* Personaje::getPosicion(){
	return rectanguloPersonaje->getPos();
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

/**
 * \brief	Se setea el estado del personaje, mediante 3 taxonomias (incompletas para el juego final).
 * 			E_PERFIL: 			determina el perfil a conciderar.
 * 			E_ACCION:			da información sobre las acciones que realiza el personaje.
 *
 * \param	\perfil
 * \param	\accion		Se utiliza detallar que tipo de acciones está realizando el personaje.
 */
/*
void Personaje::setEstado(E_PERFIL perfil, E_ACCION accion){
	estado->perfil = perfil;
	estado->accion = accion;
}

/**
 * \brief	Setea el estado del personaje.
 */
/*
void Personaje::setEstado(Estado estado){
	this->estado->perfil = estado.perfil;
	this->estado->accion = estado.accion;
}

/**
 * \return	Estado del personaje.
 */
/*
Personaje::Estado Personaje::getEstado(){
	return estado;
}
*/

void Personaje::setEstado(std::string unEstado){
	this->estado = unEstado;
}

std::string Personaje::getEstado(){
	return this->estado;
}
