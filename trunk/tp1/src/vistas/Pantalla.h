#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vista.h"
#include "../excepciones/SDL_Excepcion.h"
#include "../parseo/Config.h"
#include "../elementosJuego/personajes/Personaje.h"

class Pantalla {
private:
	int altoPx;
	int anchoPx;
	int alto;
	int ancho;
	int numeroDeCuadro;
	std::string dirImg;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	SDL_Texture * fondo;
	std::vector<Vista*> vistas;
	void agregarVistas(std::vector<ObjetoMapa*> objetos, std::vector<Personaje*> personajes);

public:
	Pantalla(Config* config);
	void inicializar() throw (SDL_Excepcion);
	void cambiar();
	void agregarVista(Vista* v);

	int getAlto();
	int getAncho();

	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
