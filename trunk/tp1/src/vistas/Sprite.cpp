#include "../vistas/Sprite.h"

SDL_Rect* crearCuadro(int x, int y, int w, int h){
	SDL_Rect* unCuadro = new SDL_Rect;
	unCuadro->x = x;
	unCuadro->y = y;
	unCuadro->w = w;
	unCuadro->h = h;
	return unCuadro;
}

std::vector<SDL_Rect*>* Sprite::listaDeCuadros() {
	std::vector<SDL_Rect*>* Cuadros= new std::vector<SDL_Rect*>();

		//Fotogramas a la izquierda
		Cuadros->push_back(crearCuadro(6,16,22,24));
		Cuadros->push_back(crearCuadro(38,16,22,24));
		Cuadros->push_back(crearCuadro(62,16,20,24));
		Cuadros->push_back(crearCuadro(94,16,18,24));
		Cuadros->push_back(crearCuadro(118,10,21,30));
		Cuadros->push_back(crearCuadro(150,16,23,25));

		//Fotogramas a la derecha

		Cuadros->push_back(crearCuadro(834,16,22,24));
		Cuadros->push_back(crearCuadro(807,16,17,24));
		Cuadros->push_back(crearCuadro(780,16,20,24));
		Cuadros->push_back(crearCuadro(750,16,18,24));
		Cuadros->push_back(crearCuadro(723,10,21,30));
		Cuadros->push_back(crearCuadro(689,16,23,25));

	return Cuadros;
}

