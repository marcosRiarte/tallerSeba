#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vista.h"
#include "../excepciones/SDL_Excepcion.h"
#include "PersonajeVista.h"
#include "ObjetoMapaVista.h"
#include "../controlador/Evento.h"
#include "../redes/Paquetes.h"

class Pantalla {
private:
	float alto;
	float ancho;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	SDL_Texture * fondo;
	/*
	 * Esta textura se va a usar como una preview de la ventana.
	 * 	Antes de imprimir en la ventana del juego, se va a seleccionar
	 * 	una porción de esta textura (zoom);
	 */
	SDL_Texture* tVentana;
	/*
	 * Son vectores de punteros porque el vector cuando realoca elementos llama a sus destructores y
	 * 	se pierden las referencias a las texturas que componen a los objetos que tiene.
	 * Se agrega logica para eliminar los vectores cuando se destruye la pantalla.
	 */
	std::vector<PersonajeVista*> personajes;
	std::vector<ObjetoMapaVista*> objetos;

	/*
	 * La pantalla se va a centrar sobre el personaje principal para habilitar
	 * 	el zoom.
	 */
	PersonajeVista* personajePrincipal;

	float zoom;
	float maxZoom;
	SDL_Rect zoomClip;

	float getMaxZoom();
	void setZoomClip(std::vector<Evento> eventos);
	void agregarPersonaje(PaquetePersonaje paquete);
	void agregarObjetoMapa(PaqueteObjeto paquete);

public:
	Pantalla(PaqueteACliente configuracion);
	void cambiar(std::vector<Evento> eventos);

	// Agrega o actualiza
	void cambiarPersonaje(PaquetePersonaje paquete);
	void cambiarObjetoMapa(PaqueteObjeto paquete);

	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
