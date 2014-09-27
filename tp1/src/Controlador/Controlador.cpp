#include <Controlador/Controlador.h>
#include "Constantes.h"

int Controlador::cambiar(std::vector<Evento*>* listaEventos) {
	for(unsigned i=0; i<listaEventos->size(); i++) {
		delete listaEventos->at(i);
	}

	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (event.key.keysym.sym == SDLK_LEFT && (state[SDL_SCANCODE_LEFT])) {
		if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
			Evento* der = new Evento(2);
			Evento* arriba = new Evento(3);
			listaEventos->push_back(der);
			listaEventos->push_back(arriba);
			return CONTINUAR;
		} else if (state[SDL_SCANCODE_RIGHT]) {
			Evento* der = new Evento(2);
			listaEventos->push_back(der);
			return CONTINUAR;
		} else {
			Evento* izq = new Evento(1);
			listaEventos->push_back(izq);
			return CONTINUAR;
		}

	}

	else if (event.key.keysym.sym == SDLK_RIGHT && (state[SDL_SCANCODE_RIGHT])) {
		if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
			Evento* izq = new Evento(1);
			Evento* arriba = new Evento(3);
			listaEventos->push_back(izq);
			listaEventos->push_back(arriba);
			return CONTINUAR;

		} else if (state[SDL_SCANCODE_LEFT]) {
			Evento* izq = new Evento(1);
			listaEventos->push_back(izq);
			return CONTINUAR;
		} else {
			Evento* der = new Evento(2);
			listaEventos->push_back(der);
			return CONTINUAR;
		}
	}

	else if (event.key.keysym.sym == SDLK_UP && (state[SDL_SCANCODE_UP])) {

		if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]){
			Evento* arriba = new Evento(3);
			listaEventos->push_back(arriba);
			return CONTINUAR;

		} else if (state[SDL_SCANCODE_LEFT]) {
			Evento* izq = new Evento(1);
			Evento* arriba = new Evento(3);
			listaEventos->push_back(izq);
			listaEventos->push_back(arriba);
			return CONTINUAR;
		} else if (state[SDL_SCANCODE_RIGHT]) {
			Evento* der = new Evento(2);
			Evento* arriba = new Evento(3);
			listaEventos->push_back(der);
			listaEventos->push_back(arriba);
			return CONTINUAR;

		}else{

		Evento* arriba = new Evento(3);
		listaEventos->push_back(arriba);
		return CONTINUAR;
		}

		}

	else if (event.key.keysym.sym == SDLK_r && (state[SDL_SCANCODE_R])) {
		Evento* reset = new Evento(4);
		listaEventos->push_back(reset);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_LEFT]){
		Evento* izq = new Evento(1);
		listaEventos->push_back(izq);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_RIGHT]){
		Evento* der = new Evento(2);
		listaEventos->push_back(der);
		return CONTINUAR;
	}

	Evento* nada= new Evento(0);
	listaEventos->push_back(nada);
	return CONTINUAR;
}


Controlador::~Controlador() {
	// TODO Auto-generated destructor stub
}

