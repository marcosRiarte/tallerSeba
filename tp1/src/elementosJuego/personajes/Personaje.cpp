#include "Personaje.h"

Personaje::Personaje(Pos* posicion) {
	pos = posicion;
	rot = 0;
	linkAMundo = nullptr;
	ancho = 34;
	alto = 45;
	this->estado= "Quieto";

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
void Personaje::setPos(Pos* posicion) {
	pos = posicion;
	rectanguloPersonaje->setPos(posicion);
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

/*
 * Devuelve el area del elemento
 */
float Personaje::getArea() {
	return 15;
}

std::string Personaje::getEstado(){
	return this->estado;
}
