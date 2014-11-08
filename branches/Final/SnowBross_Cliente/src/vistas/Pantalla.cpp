#include <iostream>
#include <string>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "../Constantes.h"
#include "Pantalla.h"
#include "ObjetoMapaVista.h"
#include "PersonajeVista.h"

//TODO - Ver el tema de los pos.ySimetrico

Pantalla::Pantalla(PaqueteACliente configuracion) {

	PaqueteInicial cInicial = configuracion.paqueteInicial;

	personajes = std::vector<PersonajeVista*>();
	objetos = std::vector<ObjetoMapaVista*>();
	ancho = cInicial.ancho;
	alto = cInicial.alto;

	ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cInicial.anchoPx, cInicial.altoPx, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		loguer->loguear("No se pudo crear la ventana principal", Log::LOG_ERR);
		throw SDL_Excepcion(((std::string)"Error creando ventana principal: ").append(SDL_GetError()));
	}

	/*
	 * Para crear el renderer, tiene que estar creada la ventana (Window)
	 */
	renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	| SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr) {
		loguer->loguear("No se pudo crear el renderer", Log::LOG_ERR);
		throw SDL_Excepcion(((std::string) "Error creando el renderer: ").append(SDL_GetError()));
	}

	fondo = IMG_LoadTexture(renderer, "img/fondo1.png");
	if (fondo == nullptr) {
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		throw SDL_Excepcion(((std::string) "Error cargando el fondo de pantalla: ").append(SDL_GetError()));
	}

	//Esta textura tiene las mismas dimensiones  que maneja el juego. De esta manera no hace falta escalado, hasta el final cuando se la pasa a la ventana principal.
	tVentana = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ancho, alto);

	//Cargo los personajes
	for(unsigned i = 0; i < configuracion.contadorPersonaje; i++)
		agregarPersonaje(configuracion.paquetePersonaje[i]);

	//Cargo los objetos
	for(unsigned i = 0; i < configuracion.contadorObjetos; i++)
		agregarObjetoMapa(configuracion.paqueteObjeto[i]);

	//selecciono el personaje principal
	unsigned int IDPersonajePrincipal = cInicial.IDPersonajePrincipal;
	for (unsigned i = 0; i < personajes.size(); i++)
		if(personajes.at(i)->getID() == IDPersonajePrincipal)
			personajePrincipal = personajes.at(i);

	zoom = 0;
	maxZoom = getMaxZoom();
}

void Pantalla::agregarPersonaje(PaquetePersonaje paquete){
	//Creo el personaje
	Pos p = Pos(paquete.x, paquete.y);
	Personaje personaje = Personaje(p);
	personaje.setID(paquete.id);
	personaje.setEstado(paquete.estado);
	//Creo la vista con el personaje creado y lo guardo en el vector de personajes.
	PersonajeVista* vista = new PersonajeVista(renderer, personaje);
	personajes.push_back(vista);
}

//TODO - FALTAAAAAAAAAAAAAAAAAAAAAA!!!!!
void Pantalla::agregarObjetoMapa(PaqueteObjeto paquete){
	//Creo el objeto
	Pos p = Pos(paquete.x, paquete.y);
	//ObjetoMapa objeto = ObjetoMapa( esEstatico, std::string color, Pos pos_cm, int rotacion, int masa, std::vector<Pos> contorno);
}


void Pantalla::cambiar(std::vector<Evento> eventos){
	//El target del renderer será la textura auxiliar tVentana de la cual luego se eligirá que parte de la misma imprimir
	SDL_SetRenderTarget(renderer, tVentana);

	//Limpio la textura
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);

	//Se cargan los personajes
	for (unsigned i = 0; i < personajes.size(); i++) {
		PersonajeVista* vistaPersonaje = personajes.at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vistaPersonaje->getVista();

		//La imprimo en la pantalla con la debida transformacion
		const SDL_Rect v = vistaPersonaje->getVentana();
		SDL_RenderCopy(renderer, textura, NULL, &v);
	}

	//Se cargan los objetos
	for (unsigned i = 0; i < objetos.size(); i++) {
		ObjetoMapaVista* vistaObjeto = objetos.at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vistaObjeto->getVista();

		//La imprimo en la pantalla con la debida transformacion
		const SDL_Rect v = vistaObjeto->getVentana();
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
	int altoPersonaje = personajePrincipal->getVentana().h;
	int anchoPersonaje = personajePrincipal->getVentana().w;

	if (ancho < alto)
		menorDimensionPantalla = ancho;
	else
		menorDimensionPantalla = alto;

	if (anchoPersonaje > altoPersonaje)
		mayorDimensionPersonaje = anchoPersonaje;
	else
		mayorDimensionPersonaje = altoPersonaje;

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

	int altoPersonaje = personajePrincipal->getVentana().h;
	int anchoPersonaje = personajePrincipal->getVentana().w;
	Pos posicionPersonaje = personajePrincipal->getPos();

	zoomClip.w = ancho - (anchoPersonaje * zoom);
	zoomClip.h = alto - (altoPersonaje * zoom);

	zoomClip.x = posicionPersonaje.getX() - (zoomClip.w / 2);
	if (zoomClip.x < 0)
		zoomClip.x = 0;
	else if (zoomClip.x + zoomClip.w > ancho)
		zoomClip.x = ancho - zoomClip.w;

	zoomClip.y = posicionPersonaje.getY() - (zoomClip.h / 2);
	if (zoomClip.y < 0)
		zoomClip.y = 0;
	else if (zoomClip.y + zoomClip.h > alto)
		zoomClip.y = alto - zoomClip.h;
}

Pantalla::~Pantalla() {
	for (unsigned i = 0; i < personajes.size(); i++)
		if (personajes.at(i) != nullptr)
			delete personajes.at(i);
	personajes.clear();
	for (unsigned i = 0; i < objetos.size(); i++)
		if (objetos.at(i) != nullptr)
			delete objetos.at(i);
	objetos.clear();
    SDL_DestroyTexture(tVentana);
	SDL_DestroyTexture(fondo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
}
