/*
 * Pantalla.cpp
 *
 *  Created on: 6/9/2014
 *      Author: pablo_000
 */
#include <iostream>
#include "Pantalla.h"

Pantalla::Pantalla(int altoPx, int anchoPx, int alto, int ancho, string dirImg) {
	this->altoPx = altoPx;
	this->anchoPx = anchoPx;
	this->alto = alto;
	this->ancho = ancho;
	this->dirImg = dirImg;
	this->ventana = nullptr;
}
/**
 * Se inicia SDL y se crea la pantalla principal.
 */
void Pantalla::inicializar() throw (SDL_Excepcion){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		// Todo agregar al Log
		const char* msg = ((string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
	ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoPx, altoPx, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		// Todo agregar al log
		cout << "Error creando Ventana: " << SDL_GetError() << std::endl;
		throw new SDL_Excepcion();
	}
}

Pantalla::~Pantalla() {
	SDL_Quit();
}

