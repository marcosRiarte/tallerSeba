#include <iostream>
#include <string>
#include "../Constantes.h"
#include "Pantalla.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>

Pantalla::Pantalla(int altoPx, int anchoPx, int alto, int ancho, const char* dirImg) {
	this->altoPx = altoPx;
	this->anchoPx = anchoPx;
	this->alto = alto;
	this->ancho = ancho;
	this->dirImg = dirImg;
	this->vistas = new std::vector<Vista*>;
	this->ventana = nullptr;
	this->renderer = nullptr;
}
/**
 * Se inicia SDL y se crea la pantalla principal.
 */
void Pantalla::inicializar() throw (SDL_Excepcion){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		loguer->loguear("No se pudo iniciar SDL",Log::LOG_ERR);
		const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
	ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoPx, altoPx, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		loguer->loguear("No se pudo crear la ventana principal", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando ventana principal: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
	renderer =  SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr){
		loguer->loguear("No se pudo crear el renderer", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando el renderer: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
	this->fondo = IMG_LoadTexture(renderer, dirImg);
	if (fondo == nullptr) {
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		const char* msg =
				((std::string) "Error cargando el fondo de pantalla: ").append(
						SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
}

SDL_Renderer* Pantalla::getRenderer(){
	return renderer;
}

void Pantalla::agregarVista(Vista * v){
	vistas->push_back(v);
}


void Pantalla::update(){
	//Limpio la pantalla
	SDL_RenderClear(renderer);
	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);

	//Se cargan los objetos
	for(unsigned i = 0; i < vistas->size(); i++ ){
		Vista* vista = vistas->at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla
		SDL_Rect* r = vista->getVentana();
		r->h = r->h*altoPx/alto;
		r->w = r->w*anchoPx/ancho;
		r->x = r->x*anchoPx/ancho;
		r->y = r->y*altoPx/alto;
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, textura, NULL, r);
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
	SDL_Quit();
}

