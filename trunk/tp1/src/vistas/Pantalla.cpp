#include <iostream>
#include <string>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../Constantes.h"
#include "Pantalla.h"
#include "ObjetoMapaVista.h"
#include "PersonajeVista.h"

Pantalla::Pantalla(Config* config) {
	this->altoPx = config->getAltoPx();
	this->anchoPx = config->getAnchoPx();
	this->alto = config->getAlto();
	this->ancho = config->getAncho();
	this->dirImg = config->getFondo();
	this->vistas = std::vector<Vista*>();
	this->ventana = nullptr;
	this->renderer = nullptr;
	this->fondo = nullptr;
	inicializar();
	agregarVistas(config->getObjetos(), config->getPersonajes());
}

/**
 * obs		Necesita que SDL este iniciado.
 */
void Pantalla::inicializar() throw (SDL_Excepcion){
	ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoPx, altoPx, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		loguer->loguear("No se pudo crear la ventana principal", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando ventana principal: ").append(SDL_GetError()).c_str();
		throw SDL_Excepcion(msg);
	}
	renderer =  SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr){
		loguer->loguear("No se pudo crear el renderer", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando el renderer: ").append(SDL_GetError()).c_str();
		throw SDL_Excepcion(msg);
	}

	this->fondo = IMG_LoadTexture(renderer, dirImg.c_str());
	if (fondo == nullptr) {
		loguer->loguear(
				"No se encontró imagen de fondo, se toma imagen de fondo por defecto",
				Log::LOG_WAR);
		this->dirImg = "img/fondoDefault.png";
		this->fondo = IMG_LoadTexture(renderer, dirImg.c_str());
		if (fondo == nullptr) {
			loguer->loguear("No se pudo crear el fondo", Log::LOG_ERR);
			const char* msg = ((std::string) "Error creando el fondo: ").append(
					SDL_GetError()).c_str();
			throw SDL_Excepcion(msg);
		}
	}
}


void Pantalla::agregarVistas(std::vector<ObjetoMapa*> objetos, std::vector<Personaje*> personajes){
	Vista* v;
	for(unsigned i = 0; i < objetos.size(); i++){
		v = new ObjetoMapaVista(renderer, objetos.at(i));
		vistas.push_back(v);
	}
	for(unsigned i = 0; i < personajes.size(); i++){
		v = new PersonajeVista(renderer, personajes.at(i));
		vistas.push_back(v);
	}
}


void Pantalla::cambiar(){
	//Limpio la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);

	//Se cargan los objetos
	for(unsigned i = 0; i < vistas.size(); i++){
		Vista* vista = vistas.at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla con la debida transformacion
		SDL_Rect r = SDL_Rect();
		const SDL_Rect v = vista->getVentana();
		r.h = v.h*altoPx/alto;
		r.w = v.w*anchoPx/ancho;
		r.x = v.x*anchoPx/ancho;
		r.y = v.y*altoPx/alto;
		SDL_RenderCopy(renderer, textura, NULL, &r);
	}
	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);
}


int Pantalla::getAlto() {
	return alto;
}
int Pantalla::getAncho(){
	return ancho;
}

Pantalla::~Pantalla() {
	for(unsigned i = 0; i < vistas.size()-1; i++){
		delete vistas.at(i);
	}
	SDL_DestroyTexture(fondo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
}


