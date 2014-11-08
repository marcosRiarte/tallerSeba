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

	/*
	 * Para crear el renderer, tiene que estar creada la ventana (Window)
	 */
	this->renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			if (renderer == nullptr){
				loguer->loguear("No se pudo crear el renderer", Log::LOG_ERR);
				const char* msg = ((std::string)"Error creando el renderer: ").append(SDL_GetError()).c_str();
				throw SDL_Excepcion(msg);
	}

	/*
	 * Ahora que se creo el renderer puedo hacer lo siguiente:
	 * - crear las vistas, el fondo y la textura que guardara un screenshot de la ventana del juego.
	 */
	this->vistas = crearVistas(config->getObjetos(), config->getPersonajes());
	this->fondo =IMG_LoadTexture(renderer, dirImg.c_str());
	if (fondo == nullptr) {
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		const char* msg = ((std::string) "Error cargando el fondo de pantalla: ").append(SDL_GetError()).c_str();
		throw SDL_Excepcion(msg);
	}

	//Esta textura tiene las mismas dimensiones  que maneja el juego. De esta manera no hace falta escalado, hasta el final cuando se la pasa a la ventana principal.
	this->tVentana = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ancho, alto);

	//La posición del personaje principal es necesaria para poder aplicar el zoom.
	this->personajePrincipal = seleccionarPersonajePrincipal(config->getPersonajes(), IDPersonajePrincipal);

	this->zoom = 0;
	this->maxZoom = getMaxZoom();
}

std::vector<Vista*> Pantalla::crearVistas(std::vector<ObjetoMapa*> objetos, std::vector<Personaje*> personajes){
	std::vector<Vista*> vector = std::vector<Vista*>();
	for(unsigned i = 0; i < objetos.size(); i++)
		vector.push_back(new ObjetoMapaVista(renderer, objetos.at(i)));

	for(unsigned i = 0; i < personajes.size(); i++)
		vector.push_back(new PersonajeVista(renderer, personajes.at(i)));
	return vector;
}

Personaje* Pantalla::seleccionarPersonajePrincipal(std::vector<Personaje*> personajes, int IDPersonajePrincipal){
	for(unsigned i = 0; i < personajes.size(); i++)
		if (personajes.at(i)->getID() == IDPersonajePrincipal)
			return personajes.at(i);
	return nullptr; //TODO - deberia arrojar una excepcion si no lo encuentra.
}

void Pantalla::cambiar(std::vector<Evento> eventos){
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

	//Seteo el clip que se va a mostrar - zoom
	setZoomClip(eventos);

	//Modifico el target del render para que apunte a la ventana principal
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, tVentana, &zoomClip, NULL);
	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);
}

float Pantalla::getMaxZoom(){
	float menorDimensionPantalla;
	float mayorDimensionPersonaje;

	if (ancho < alto)
		menorDimensionPantalla = ancho;
	else
		menorDimensionPantalla = alto;

	if (personajePrincipal->getAncho() > personajePrincipal->getAlto())
		mayorDimensionPersonaje = personajePrincipal->getAncho();
	else
		mayorDimensionPersonaje = personajePrincipal->getAlto();

	return ( menorDimensionPantalla / mayorDimensionPersonaje ) - 1;
}

/**
 * Setea el zoomClip teniendo en cuenta los inputs.
 * 	zoomClip es un SDL_Rect que se utiliza para tomar una porción del toda la textura generada.
 * 	Por ende, se elige ese rectangulo y se amplia a toda la pantalla, justo antes de retornar.
 * 	Dandole de esta manera el efecto de zoom.
 */
void Pantalla::setZoomClip(std::vector<Evento> eventos) {
	//determino el zoom producto de los inputs
	for (unsigned i = 0; i < eventos.size(); i++)
		switch (eventos.at(i).getTecla()) {
			case (TECLA_MAS):
				if(zoom < maxZoom )
					zoom = zoom + 0.1;
				break;
			case (TECLA_MENOS):
				if(zoom > 0)
					zoom = zoom - 0.1;
				break;
		}

	zoomClip.w = ancho - (personajePrincipal->getAncho() * zoom);
	zoomClip.h = alto - (personajePrincipal->getAlto() * zoom);

	zoomClip.x = personajePrincipal->getPos().getX() - (zoomClip.w / 2);
	if (zoomClip.x < 0)
		zoomClip.x = 0;
	else if (zoomClip.x + zoomClip.w > ancho)
		zoomClip.x = ancho - zoomClip.w;

	zoomClip.y = personajePrincipal->getPos().ySimetrico().getY() - (zoomClip.h / 2);
	if (zoomClip.y < 0)
		zoomClip.y = 0;
	else if (zoomClip.y + zoomClip.h > alto)
		zoomClip.y = alto - zoomClip.h;

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
