/*
 * Representa un evento de entrada
 */

#include "Evento.h"
#include <iostream>

Evento::Evento() {
	this->teclaIngresada="nada";
}

// geter y seter para la tecla
void Evento::setTecla(string tecla) {
	this->teclaIngresada = tecla;
}

string Evento::getTecla() {
	return this->teclaIngresada;
}

Evento::~Evento() {
}
