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
	this->unConfig = config;
	this->camara={ 0, 0, anchoPx, altoPx };
	this->zoom=1.1;
	inicializar();
	agregarVistas(config->getObjetos(), config->getPersonajes());

	//Se carga el personaje
	Vista* vista = vistas.at(vistas.size()-1);
	personaje = vista->getVentana();
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


void Pantalla::cambiar(std::vector<Evento>* ListaDeEventos){

	//Se carga el personaje
	Vista* vista = vistas.at(vistas.size()-1);

	//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
	SDL_Texture* textura = vista->getVista();

	//La imprimo en la pantalla con la debida transformacion
	const SDL_Rect v = vista->getVentana();

	for (unsigned i = 0; i < ListaDeEventos->size(); i++) {
		if (ListaDeEventos->at(i).getTecla() == TECLA_MAS) {
			camara.w = camara.w / zoom;
			camara.h = camara.h / zoom;
		}
		if (ListaDeEventos->at(i).getTecla() == TECLA_MENOS) {
			camara.w = camara.w * zoom;
			camara.h = camara.h * zoom;
		}
	}

	//Se centra la camara alrededor del personaje
	camara.x = (v.x + (v.w / 2)) - anchoPx / 2;
	camara.y = (v.y + (v.h / 2)) - altoPx / 2;

	//Mantener la camara en los limites
	if (camara.x < 0) {
		camara.x = 0;
	}
	if (camara.y < 0) {
		camara.y = 0;
	}
	if (camara.x > ancho - camara.w) {
		camara.x = ancho - camara.w;
	}
	if (camara.y > alto - camara.h) {
		camara.y = alto - camara.h;
	}

	personaje.x = v.x-camara.x;
	personaje.y = v.y-camara.y;

/*
	for (unsigned i = 0; i < ListaDeEventos->size(); i++) {
		if (ListaDeEventos->at(i).getTecla() == TECLA_MAS) {
			personaje.h = personaje.h*zoom;
			personaje.w = personaje.w*zoom;
		}
		if (ListaDeEventos->at(i).getTecla() == TECLA_MENOS) {
			personaje.h = personaje.h/zoom;
			personaje.w = personaje.w/zoom;
		}
	}
*/

	//Limpio la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Cargo el fondo de pantalla en el renderer
	SDL_Rect cuadrado = { 0, 0, anchoPx, altoPx };
	SDL_RenderCopy(renderer, fondo, &camara, &cuadrado);

	//Cargo el personaje en el renderer
	SDL_RenderCopy(renderer, textura, NULL, &personaje);

	//Se cargan los objetos
	for(unsigned i = 0; i < vistas.size()-1; i++){
		Vista* vista = vistas.at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla con la debida transformacion
		SDL_Rect rectObjeto = SDL_Rect();
		const SDL_Rect v = vista->getVentana();

		rectObjeto.h = v.h;
		rectObjeto.w = v.w;
		rectObjeto.x = v.x-camara.x;
		rectObjeto.y = v.y-camara.y;
		SDL_RenderCopyEx(renderer, textura, NULL, &rectObjeto, -(unConfig->getObjetos().at(i)->getRotacion()), NULL, SDL_FLIP_NONE);
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

void Pantalla::hacerZoom(int x, int y, float escalaAncho, float escalaAlto, SDL_Rect rectangulo){
	rectangulo.x = x - (rectangulo.w * escalaAncho - rectangulo.w) / 2;
	rectangulo.y = y - (rectangulo.h * escalaAlto - rectangulo.h) / 2;
	rectangulo.w = (rectangulo.w * escalaAncho) +0.5;
	rectangulo.h = (rectangulo.h * escalaAlto) +0.5;
}

Pantalla::~Pantalla() {
	for(unsigned i = 0; i < vistas.size()-1; i++){
		delete vistas.at(i);
	}
	SDL_DestroyTexture(fondo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
}


