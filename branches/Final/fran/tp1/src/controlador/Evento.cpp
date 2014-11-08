/*
 * Representa un evento de entrada
 */

#include "Evento.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Constantes.h"
#include "../elementosJuego/objetos/ObjetoMapa.h"

Evento::Evento() {
	this->teclaIngresada=TECLA_NADA;
}

Evento::Evento(int evento) {
	this->teclaIngresada=evento;
}

// geter y seter para la tecla
void Evento::setTecla(int tecla) {
	this->teclaIngresada = tecla;
}

int Evento::getTecla() {
	return this->teclaIngresada;
}

void procesarTecla(){

}

Evento::~Evento() {
}
