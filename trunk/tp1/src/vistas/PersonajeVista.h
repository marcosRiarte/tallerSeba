#ifndef PERSONAJEVISTA_H_
#define PERSONAJEVISTA_H_

#include "Vista.h"
#include "../personajes/Personaje.h"

class PersonajeVista: public Vista {
private:
	Personaje* personaje;
public:
	PersonajeVista(Personaje* p);
	SDL_Texture* getVista();
	virtual ~PersonajeVista();
};

#endif /* PERSONAJEVISTA_H_ */
