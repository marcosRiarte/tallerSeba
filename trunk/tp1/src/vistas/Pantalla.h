#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../excepciones/SDL_Excepcion.h"
#include "ObjetoMapaVista.h"
#include "../parseo/Config.h"
#include "CreadorDeTexturas.h"
#include "Sprite.h"

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
	std::vector<Vista*>* vistas;
	std::vector<SDL_Rect*>* listaDeCuadros;
	CreadorDeTexturas* HojaDeSpritesDeTextura;
	void agregarVistas(std::vector<ObjetoMapa*>* objetos);
public:
	Pantalla(Config* config);
	void inicializar() throw (SDL_Excepcion);
	void cambiar();
	SDL_Renderer* getRenderer();
	void agregarVista(Vista* v);

	int getAlto();
	int getAncho();

	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
