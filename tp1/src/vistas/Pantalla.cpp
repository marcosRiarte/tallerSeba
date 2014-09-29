#include <iostream>
#include <string>
#include "../Constantes.h"
#include "Pantalla.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>

Pantalla::Pantalla(Config* config) {
	this->altoPx = config->getAltoPx();
	this->anchoPx = config->getAnchoPx();
	this->alto = config->getAlto();
	this->ancho = config->getAncho();
	this->numeroDeCuadro = 0;
	this->dirImg = config->getFondo();
	this->vistas = nullptr;
	this->ventana = nullptr;
	this->renderer = nullptr;
	this->fondo = nullptr;
	this->listaDeCuadros = nullptr;
	this->HojaDeSpritesDeTextura= new CreadorDeTexturas();
	inicializar();
	this->agregarVistas(config->getObjetos());
}

/**
 * obs		Necesita que SDL este iniciado.
 */
void Pantalla::inicializar() throw (SDL_Excepcion){
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

	//Paso a const char* el string del nombre de la imagen.
			const char* dirFondo = dirImg.c_str();

	this->fondo = IMG_LoadTexture(renderer, dirFondo);
	if (fondo == nullptr) {
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		const char* msg =
				((std::string) "Error cargando el fondo de pantalla: ").append(
						SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}

	//Cargar texturas del sprite.
	if (!HojaDeSpritesDeTextura->cargarDesde("img/SnowSprite.bmp",renderer)) {
		std::string errorTextura = "Imposible cargar la textura desde img/SnowSprite.bmp";
					const char* errorCargaTextura = errorTextura.c_str();
							loguer->loguear(errorCargaTextura,Log::LOG_ERR);
	} else {
		listaDeCuadros = Sprite::listaDeCuadros();
	}
}

SDL_Renderer* Pantalla::getRenderer(){
	return renderer;
}

void Pantalla::agregarVistas(std::vector<ObjetoMapa*>* objetos){
	vistas = new std::vector<Vista*>;
	Vista* v;
	for(unsigned i = 0; i < objetos->size(); i++){
		v = new ObjetoMapaVista(renderer, objetos->at(i));
		vistas->push_back(v);
	}
}


void Pantalla::cambiar(){
	//Limpio la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);

	//Renderizar el sprite
	SDL_Rect* cuadroActual = listaDeCuadros->at(numeroDeCuadro/12);
	HojaDeSpritesDeTextura->render((cuadroActual->w) / 2,(cuadroActual->h) / 2, cuadroActual, renderer);

	//Se cargan los objetos
	for(unsigned i = 0; i < vistas->size(); i++ ){
		Vista* vista = vistas->at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla con la debida transformacion
		SDL_Rect* r = new SDL_Rect();
		r->h = vista->getVentana()->h*altoPx/alto;
		r->w = vista->getVentana()->w*anchoPx/ancho;
		r->x = vista->getVentana()->x*anchoPx/ancho;
		r->y = vista->getVentana()->y*altoPx/alto;
		SDL_RenderCopy(renderer, textura, NULL, r);
		SDL_DestroyTexture(textura);
	}

	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);

	//Siguiente cuadro
	++numeroDeCuadro;
	//Ciclado de la animación
	if (numeroDeCuadro / 12 >= 12) {
		numeroDeCuadro = 0;
	}

}


int Pantalla::getAlto() {
	return alto;
}
int Pantalla::getAncho(){
	return ancho;
}

Pantalla::~Pantalla() {}

