#ifndef VISTA_H_
#define VISTA_H_

#include <SDL2/SDL.h>

class Vista {
public:
	virtual SDL_Texture* getVista() = 0;
	virtual ~Vista(){};
};

#endif /* VISTA_H_ */