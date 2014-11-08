#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vista.h"
#include "../excepciones/SDL_Excepcion.h"
#include "../parseo/Config.h"
#include "PersonajeVista.h"
#include "../controlador/Evento.h"

class Pantalla {
private:
	float factorX;
	float factorY;
	int alto;
	int ancho;
	int numeroDeCuadro;
	std::string dirImg;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	SDL_Texture * fondo;
	/*
	 * Esta textura se va a usar como una preview de la ventana.
	 * 	Antes de imprimir en la ventana del juego, se va a seleccionar
	 * 	una porción de esta textura (zoom);
	 */
	SDL_Texture* tVentana;
	std::vector<Vista*> vistas;

	/*
	 * La pantalla se va a centrar sobre el personaje principal para habilitar
	 * 	el zoom.
	 */
	Personaje* personajePrincipal;

	float zoom;
	float maxZoom;
	SDL_Rect zoomClip;

	std::vector<Vista*> crearVistas(std::vector<ObjetoMapa*> objetos, std::vector<Personaje*> personajes);
	Personaje* seleccionarPersonajePrincipal(std::vector<Personaje*> personajes, int IDPersonajePrincipal);
	float getMaxZoom();
	void setZoomClip(std::vector<Evento> eventos);

public:
	Pantalla(Config* config, int IDPersonajePrincipal);
	void cambiar(std::vector<Evento> eventos);

	int getAlto();
	int getAncho();

	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
