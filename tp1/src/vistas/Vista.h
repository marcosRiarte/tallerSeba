#ifndef VISTA_H_
#define VISTA_H_

#include <SDL2/SDL.h>

class Vista {
protected:
	SDL_Renderer* renderer;
public:
	virtual SDL_Surface* getVista() = 0;
	virtual ~Vista(){};
};

#endif /* VISTA_H_ */
