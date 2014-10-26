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
	this->altoPx1 = config->getAltoPx();
	this->anchoPx1 = config->getAnchoPx();
	this->alto = config->getAlto();
	this->ancho = config->getAncho();
	this->dirImg = config->getFondo();
	this->vistas = std::vector<Vista*>();
	this->ventana = nullptr;
	this->renderer = nullptr;
	this->fondo = nullptr;
	this->unConfig = config;
	this->camara={ 0, 0, anchoPx, altoPx };
	this->zoomout=1.01;
	this->zoomin=0.99;
	inicializar();
	agregarVistas(config->getObjetos(), config->getPersonajes());

	//Se carga el personaje
	Vista* vista = vistas.at(vistas.size()-1);
	personaje = vista->getVentana();

	//Cargo el fondo de pantalla en el renderer
	cuadrado = { 0, 0, anchoPx, altoPx };

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

	//Limpio la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//Cargo el fondo de pantalla en el renderer
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


	for (unsigned i = 0; i < ListaDeEventos->size(); i++) {
		if (ListaDeEventos->at(i).getTecla() == TECLA_MAS && zoomin * altoPx>=250 && zoomin * anchoPx>=500) {
			SDL_RenderSetLogicalSize(renderer,zoomin * anchoPx * (ancho / alto), zoomin * altoPx);
			anchoPx = anchoPx * zoomin * (ancho / alto);
			altoPx = zoomin * altoPx;
			camara.w=camara.w*zoomin* (ancho / alto);
			camara.h=camara.h*zoomin;
			cuadrado.w=cuadrado.w*zoomin* (ancho / alto);
			cuadrado.h=cuadrado.h*zoomin;

		}

		if (ListaDeEventos->at(i).getTecla() == TECLA_MENOS && altoPx<=altoPx1*2 && anchoPx<=anchoPx1*2) {
			SDL_RenderSetLogicalSize(renderer,
			zoomout * anchoPx * (ancho / alto), zoomout * altoPx);
			anchoPx = anchoPx * zoomout * (ancho / alto);
			altoPx = zoomout * altoPx;
			camara.w=camara.w*zoomout* (ancho / alto);
			camara.h=camara.h*zoomout;
			cuadrado.w=cuadrado.w*zoomout* (ancho / alto);
			cuadrado.h=cuadrado.h*zoomout;
		}
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


