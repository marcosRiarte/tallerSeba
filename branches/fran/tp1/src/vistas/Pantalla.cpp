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
	this->vistas = nullptr;
	this->ventana = nullptr;
	this->renderer = nullptr;
	this->fondo = nullptr;
	inicializar();
	agregarVistas(config->getObjetos(),config->getPersonajes());
//	this->numeroDeCuadro = 0;
//	this->unSprite = nullptr;
//	this->listaDeCuadros = new std::vector<SDL_Rect*>();
//	this->HojaDeSpritesDeTextura= new CreadorDeTexturas();
//	this->config = config;
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
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		const char* msg =
				((std::string) "Error cargando el fondo de pantalla: ").append(
						SDL_GetError()).c_str();
		throw SDL_Excepcion(msg);
	}
/*
	//Cargar texturas del sprite.
	if (!HojaDeSpritesDeTextura->cargarDesde("img/SnowSprite.png",renderer)) {
		std::string errorTextura = "Imposible cargar la textura desde img/SnowSprite.bmp";
					const char* errorCargaTextura = errorTextura.c_str();
							loguer->loguear(errorCargaTextura,Log::LOG_ERR);
	} else {
		HojaDeSpritesDeTextura->setAlpha(255);
		HojaDeSpritesDeTextura->setBlend(SDL_BLENDMODE_BLEND);
		unSprite = new Sprite();
	}
*/
}

void Pantalla::agregarVistas(std::vector<ObjetoMapa>* objetos, std::vector<Personaje>* personajes){
	vistas = new std::vector<Vista*>();
	Vista* v;
	for(unsigned i = 0; i < objetos->size(); i++){
		v = new ObjetoMapaVista(renderer, &objetos->at(i));
		vistas->push_back(v);
	}
	for(unsigned i = 0; i < personajes->size(); i++){
		v = new PersonajeVista(renderer, &personajes->at(i));
		vistas->push_back(v);
	}

}


void Pantalla::cambiar(){
	//Limpio la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);

	//Se cargan los objetos
	for(unsigned i = 0; i < vistas->size(); i++){
		Vista* vista = vistas->at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla con la debida transformacion
		SDL_Rect r = SDL_Rect();
		const SDL_Rect* v = vista->getVentana();
		r.h = v->h*altoPx/alto;
		r.w = v->w*anchoPx/ancho;
		r.x = v->x*anchoPx/ancho;
		r.y = v->y*altoPx/alto;
		SDL_RenderCopy(renderer, textura, NULL, &r);
		SDL_DestroyTexture(textura);
	}
/*
	//Se carga el objeto personaje
	Vista* unaVista = vistas->at(vistas->size()-1);

	//"CayendoIzq","SaltandoIzq"),,"CaminandoIzq","CayendoDer","SaltandoDer","CaminandoDer","Quieto"

	if(config->getPersonajes()->at(0)->getEstado()=="QuietoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("QuietoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="QuietoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("QuietoDer");
			}else if(config->getPersonajes()->at(0)->getEstado()=="CayendoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CayendoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="SaltandoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("SaltandoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CaminandoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CaminandoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CayendoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CayendoDer");
	}else if(config->getPersonajes()->at(0)->getEstado()=="SaltandoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("SaltandoDer");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CaminandoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CaminandoDer");
	}

	//Renderizamos el sprite

		SDL_Rect* cuadroActual = listaDeCuadros->at((numeroDeCuadro/2)/(listaDeCuadros->size()));
	HojaDeSpritesDeTextura->render((unaVista->getVentana()->x),(unaVista->getVentana()->y),config->getPersonajes()->at(0)->getAncho(),config->getPersonajes()->at(0)->getAlto(), cuadroActual, renderer);
*/
	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);
/*
	//Siguiente cuadro
	++numeroDeCuadro;
	//Ciclado de la animación
	if ((numeroDeCuadro/2 / listaDeCuadros->size()) >= (listaDeCuadros->size())) {
		numeroDeCuadro = 0;
	}
*/
}


int Pantalla::getAlto() {
	return alto;
}
int Pantalla::getAncho(){
	return ancho;
}

Pantalla::~Pantalla() {
	for(unsigned i = 0; i < vistas->size(); i++){
		delete vistas->at(i);
	}
	delete vistas;
	SDL_DestroyTexture(fondo);
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
}


