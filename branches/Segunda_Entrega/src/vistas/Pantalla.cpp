#include <iostream>
#include <string>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../Constantes.h"
#include "Pantalla.h"
#include "ObjetoMapaVista.h"
#include "PersonajeVista.h"

Pantalla::Pantalla(Config* config, int IDPersonajePrincipal) {
	this->alto = config->getAlto();
	this->ancho = config->getAncho();
	this->factorX = (float) config->getAnchoPx() / (float) ancho;
	this->factorY = (float) config->getAltoPx() / (float) alto;
	this->dirImg = config->getFondo();

	this->ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ancho*factorX, alto*factorY, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		loguer->loguear("No se pudo crear la ventana principal", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando ventana principal: ").append(SDL_GetError()).c_str();
		throw SDL_Excepcion(msg);
	}

	this->renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			if (renderer == nullptr){
				loguer->loguear("No se pudo crear el renderer", Log::LOG_ERR);
				const char* msg = ((std::string)"Error creando el renderer: ").append(SDL_GetError()).c_str();
				throw SDL_Excepcion(msg);
	}


	this->vistas = crearVistas(config->getObjetos(), config->getPersonajes());

	this->fondo =IMG_LoadTexture(renderer, dirImg.c_str());
	if (fondo == nullptr) {
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		const char* msg = ((std::string) "Error cargando el fondo de pantalla: ").append(SDL_GetError()).c_str();
		throw SDL_Excepcion(msg);
	}

	// Esta textura tiene las mismas dimensiones  que maneja el juego. De esta manera no hace falta escalado, hasta el final cuando se la pasa a la ventana principal.
	this->tVentana = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ancho, alto);

	//this->personajePrincipal = seleccionarPersonajePrincipal(vistas, IDPersonajePrincipal);
}

std::vector<Vista*> Pantalla::crearVistas(std::vector<ObjetoMapa*> objetos, std::vector<Personaje*> personajes){
	std::vector<Vista*> vector = std::vector<Vista*>();

	for(unsigned i = 0; i < objetos.size(); i++)
		vector.push_back(new ObjetoMapaVista(renderer, objetos.at(i)));

	for(unsigned i = 0; i < personajes.size(); i++)
		vector.push_back(new PersonajeVista(renderer, personajes.at(i)));

	return vector;
}

void Pantalla::cambiar(){
	//El target del renderer será la textura auxiliar tVentana de la cual luego se eligirá que parte de la misma imprimir
	SDL_SetRenderTarget(renderer, tVentana);

	//Limpio la textura
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);

	//Se cargan los objetos
	for (unsigned i = 0; i < vistas.size(); i++) {
		Vista* vista = vistas.at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla con la debida transformacion
		const SDL_Rect v = vista->getVentana();
		SDL_RenderCopy(renderer, textura, NULL, &v);
	}

	/*
	 * TODO Hay que borrar desde acá - TESTING
	 */
/*	const SDL_Rect r1 = p->getVentana();
	SDL_Rect r2;
	r2.h = r1.h + 200;
	r2.w = r1.w + 200;
	r2.x = r1.x - 100;
	r2.y = r1.y - 100;
*/
	/*
	 * TODO - Hay que borrar hasta acá - TESTING
	 */

	//Modifico el target del render para que apunte a la ventana principal
	SDL_SetRenderTarget(renderer, NULL);
//	SDL_RenderCopy(renderer, tVentana, &r2, NULL);
	SDL_RenderCopy(renderer, tVentana, NULL, NULL);
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
	for(unsigned i = 0; i < vistas.size(); i++){
		delete vistas.at(i);
	}
	SDL_DestroyTexture(fondo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_DestroyTexture(tVentana);
}
