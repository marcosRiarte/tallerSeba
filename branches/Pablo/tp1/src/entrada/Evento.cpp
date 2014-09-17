/*
 * Representa un evento de entrada
 */

#include "Evento.h"

Evento::Evento() {
	this->teclaIngresada=teclaNada;
}

Evento::Evento(int tecla) {
	this->teclaIngresada=tecla;
}

// geter y seter para la tecla
void Evento::setTecla(int tecla) {
	this->teclaIngresada = tecla;
}

int Evento::getTecla() {
	return this->teclaIngresada;
}

Evento::~Evento() {
}
