#ifndef VISTA_H_
#define VISTA_H_

#include <SDL2/SDL.h>

class Vista {
protected:
	SDL_Renderer* renderer;
	SDL_Texture* textura;
	SDL_Rect ventana;
	unsigned int ID = 0;
	virtual void setID() = 0;
public:
	virtual SDL_Texture* getVista() = 0;
	virtual SDL_Rect getVentana() = 0;
	unsigned int getID(){
		if (ID == 0)
			setID();
		return ID;
	}
	virtual ~Vista(){
		SDL_DestroyTexture(textura);
	};
};

#endif /* VISTA_H_ */
