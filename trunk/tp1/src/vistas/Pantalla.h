#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vista.h"
#include "../excepciones/SDL_Excepcion.h"
#include "../parseo/Config.h"
#include "../elementosJuego/personajes/Personaje.h"
#include "../controlador/Evento.h"

class Pantalla {
private:
	int altoPx;
	int anchoPx;
	int alto;
	int ancho;
	int numeroDeCuadro;
	float zoom;
	std::string dirImg;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	SDL_Texture * fondo;
	std::vector<Vista*> vistas;
	SDL_Rect camara;
	SDL_Rect personaje;
	void agregarVistas(std::vector<ObjetoMapa*> objetos, std::vector<Personaje*> personajes);
	Config* unConfig;
public:
	Pantalla(Config* config);
	void inicializar() throw (SDL_Excepcion);
	void cambiar(std::vector<Evento>* ListaDeEventos);
	void agregarVista(Vista* v);
	void hacerZoom(int x, int y, float escalaAncho, float escalaAlto, SDL_Rect rectangulo);

	int getAlto();
	int getAncho();

	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
