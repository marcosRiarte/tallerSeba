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
#include "../objetos/ObjetoMapa.h"
#include "../vistas/PersonajeVista.h"

Evento::Evento() {
	this->teclaIngresada=teclaNada;
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
