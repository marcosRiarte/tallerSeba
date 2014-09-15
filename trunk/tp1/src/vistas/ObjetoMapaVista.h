#ifndef OBJETOMAPAVISTA_H_
#define OBJETOMAPAVISTA_H_

#include <SDL2/SDL.h>
#include "../objetos/ObjetoMapa.h"

class ObjetoMapaVista {
private:
	ObjetoMapa* objeto;
public:
	ObjetoMapaVista(ObjetoMapa* o);
	SDL_Surface* getVista();
	virtual ~ObjetoMapaVista();
};

#endif /* OBJETOMAPAVISTA_H_ */
