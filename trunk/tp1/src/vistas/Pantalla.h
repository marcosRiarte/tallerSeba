#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../excepciones/SDL_Excepcion.h"

using namespace std;

class Pantalla {
private:
	int altoPx;
	int anchoPx;
	int alto;
	int ancho;
	string dirImg;
	SDL_Window *ventana;
public:
	Pantalla(int altoPx, int anchoPx, int alto, int ancho, string dirImg);
	void inicializar()throw(SDL_Excepcion);
	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
