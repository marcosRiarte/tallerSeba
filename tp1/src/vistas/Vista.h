#ifndef VISTA_H_
#define VISTA_H_

#include <SDL2/SDL.h>
#include "../elementosJuego/objetos/ObjetoMapa.h"
#include "../controlador/Evento.h"

class Vista {
protected:
	SDL_Renderer* renderer;
	SDL_Rect ventana;
	SDL_Texture* textura;
	SDL_Texture* texturaCirculo;
	SDL_Surface *superficie;
	SDL_Surface *superficieCirculo;
public:
	virtual SDL_Texture* getVista() = 0;
	virtual const SDL_Rect getVentana() = 0;
	void setRenderer(SDL_Renderer* r){
		renderer = r;
	};
virtual ~Vista(){
		SDL_DestroyTexture(textura);
		SDL_FreeSurface( superficie );
		SDL_FreeSurface( superficieCirculo );
	};
};

#endif /* VISTA_H_ */
