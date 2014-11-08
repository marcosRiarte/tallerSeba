#include "Personaje.h"
#include "../../Constantes.h"

#include<iostream>

Personaje::Personaje(Pos posicion) {
	pos = posicion;
	rot = 0;
	linkAMundo = nullptr;
	ancho = ANCHO_PERSONAJE_UN;
	alto = ALTO_PERSONAJE_UN;
	masa = MASA_PERSONAJE;
	estado.perfil = E_PERFIL::IZQUIERDA;
	estado.accion = E_ACCION::QUIETO;
	friccion = FRICCION_DEL_PERSONAJE;
	crearContorno();
	calcularArea();
}

/*
 * Devuelve el area del elemento
 */
void Personaje::calcularArea() {
	area = alto * ancho;
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

/*
 * Devuelve el contorno del personaje
 */
void Personaje::crearContorno() {
	Pos posicion1 = Pos(getAncho() / 2, getAlto() / 2);
	vertices.push_back(posicion1);
	Pos posicion2 = Pos(- getAncho() / 2, getAlto() / 2);
	vertices.push_back(posicion2);
	Pos posicion3 = Pos(- getAncho() / 2, - getAlto() / 2);
	vertices.push_back(posicion3);
	Pos posicion4 = Pos( getAncho() / 2, - getAlto() / 2);
	vertices.push_back(posicion4);
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

bool Personaje::esEstatico() {
	return false;
}

bool Personaje::esCirculo() {
	return false;
}

int Personaje::getID(){
	return 0;//ID;
}

Personaje::~Personaje() {
}
