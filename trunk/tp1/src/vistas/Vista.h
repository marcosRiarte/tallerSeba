#ifndef VISTA_H_
#define VISTA_H_

#include <SDL2/SDL.h>

class Vista {
protected:
	SDL_Renderer* renderer;
public:
	virtual SDL_Texture* getVista() = 0;
	void setRenderer(SDL_Renderer* r){
		renderer = r;
	};
	virtual ~Vista(){};
};

#endif /* VISTA_H_ */
