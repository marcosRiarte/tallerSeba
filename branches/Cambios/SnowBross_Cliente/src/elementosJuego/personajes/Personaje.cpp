#include "Personaje.h"
#include "../../Constantes.h"

Personaje::Personaje() {
	pos = Pos();
	ancho = ANCHO_PERSONAJE_UN;
	alto = ALTO_PERSONAJE_UN;
	estado.perfil = E_PERFIL::IZQUIERDA;
	estado.accion = E_ACCION::QUIETO;
}

Personaje::Personaje(Pos posicion) {
	pos = posicion;
	ancho = ANCHO_PERSONAJE_UN;
	alto = ALTO_PERSONAJE_UN;
	estado.perfil = E_PERFIL::IZQUIERDA;
	estado.accion = E_ACCION::QUIETO;
}

/*
 * Getter para alto y ancho del personaje en unidades reales
 */
int Personaje::getAlto() {
	return alto;
}
int Personaje::getAncho() {
	return ancho;
}


/**
 * \brief	Se setea el estado del personaje, mediante 3 taxonomias (incompletas para el juego final).
 * 			E_PERFIL: 			determina el perfil a conciderar.
 * 			E_ACCION:			da información sobre las acciones que realiza el personaje.
 *
 * \param	\perfil
 * \param	\accion		Se utiliza detallar que tipo de acciones está realizando el personaje.
 */
void Personaje::setEstado(E_PERFIL perfil, E_ACCION accion) {
	estado.perfil = perfil;
	estado.accion = accion;
}

/**
 * \brief	Setea el estado del personaje.
 */

void Personaje::setEstado(Estado estado) {
	this->estado.perfil = estado.perfil;
	this->estado.accion = estado.accion;
}

/**
 * \return	Estado del personaje.
 */
Personaje::Estado Personaje::getEstado() {
	return estado;
}

Personaje::~Personaje() {}
