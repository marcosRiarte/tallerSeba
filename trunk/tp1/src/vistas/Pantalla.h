#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../excepciones/SDL_Excepcion.h"
#include "ObjetoMapaVista.h"
#include "../parseo/Config.h"

class Pantalla {
private:
	int altoPx;
	int anchoPx;
	int alto;
	int ancho;
	const char* dirImg;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	SDL_Texture * fondo;
	std::vector<Vista*>* vistas;

	void agregarVistas(std::vector<ObjetoMapa*>* objetos);
public:
	Pantalla(Config* config);
	void inicializar() throw (SDL_Excepcion);
	void update();
	SDL_Renderer* getRenderer();
	void agregarVista(Vista* v);

	int getAlto();
	int getAncho();

	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
