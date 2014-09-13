#include <iostream>
#include <string>
#include "Pantalla.h"

Pantalla::Pantalla(int altoPx, int anchoPx, int alto, int ancho, const char* dirImg) {
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
		const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
	ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoPx, altoPx, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		// Todo agregar al log
		const char* msg = ((std::string)"Error creando ventana principal: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
}

Pantalla::~Pantalla() {
	SDL_Quit();
}

