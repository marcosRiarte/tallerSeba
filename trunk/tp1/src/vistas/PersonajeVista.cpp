#include "PersonajeVista.h"

PersonajeVista::PersonajeVista(Personaje* p) {
	personaje = p;
}

SDL_Texture* PersonajeVista::getVista(){
	return nullptr;
}

const SDL_Rect* PersonajeVista::getVentana(){
	return nullptr;
}

PersonajeVista::~PersonajeVista() {
	// TODO Auto-generated destructor stub
}

