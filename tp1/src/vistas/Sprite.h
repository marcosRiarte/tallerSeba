#ifndef  _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Sprite{
	public:
	static std::vector<SDL_Rect*>* listaDeCuadros();
};

#endif


