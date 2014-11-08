#include "Evento.h"

Evento::Evento() {
	this->teclaIngresada = TECLA_NADA;
}

Evento::Evento(int evento) {
	this->teclaIngresada = evento;
}

// geter y seter para la tecla
void Evento::setTecla(int tecla) {
	this->teclaIngresada = tecla;
}

int Evento::getTecla() {
	return this->teclaIngresada;
}

void procesarTecla() {

}

Evento::~Evento() {
}
