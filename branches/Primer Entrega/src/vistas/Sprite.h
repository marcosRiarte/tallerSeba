#ifndef  _SPRITE_H_
#define _SPRITE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

class Sprite{
private:
	std::vector<SDL_Rect*>* CayendoDer;
	std::vector<SDL_Rect*>* SaltandoDer;
	std::vector<SDL_Rect*>* CaminandoDer;

	std::vector<SDL_Rect*>* CayendoIzq;
	std::vector<SDL_Rect*>* SaltandoIzq;
	std::vector<SDL_Rect*>* CaminandoIzq;

	std::vector<SDL_Rect*>* Quieto;
	std::vector<SDL_Rect*>* QuietoDer;
	std::vector<SDL_Rect*>* QuietoIzq;

	public:
	Sprite();
	std::vector<SDL_Rect*>* listaDeCuadros(std::string tipoMov);
};

#endif


