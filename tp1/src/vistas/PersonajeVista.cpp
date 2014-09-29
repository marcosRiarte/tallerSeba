#include "PersonajeVista.h"

PersonajeVista::PersonajeVista(SDL_Renderer* r, Personaje* p) {
	renderer = r;
	personaje = p;
	ventana->h = personaje->getAlto();
	ventana->w = personaje->getAncho();
}

SDL_Texture* PersonajeVista::getVista() {
	return nullptr;
}

const SDL_Rect* PersonajeVista::getVentana() {
	Pos* p = personaje->getPosicion()->ySimetrico();
	ventana->x = p->getX() - ventana->w / 2;
	ventana->y = p->getY() - ventana->h / 2;
	return ventana;
}

PersonajeVista::~PersonajeVista() {
	// TODO Auto-generated destructor stub
}

