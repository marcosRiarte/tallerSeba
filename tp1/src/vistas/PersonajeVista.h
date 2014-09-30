#ifndef PERSONAJEVISTA_H_
#define PERSONAJEVISTA_H_

#include "Vista.h"
#include "../personajes/Personaje.h"

class PersonajeVista: public Vista {
private:
	Personaje* personaje;

	std::vector<SDL_Rect*>* vSpritesQuieto;
	std::vector<SDL_Rect*>* vSpritesDesplazamiento;
	std::vector<SDL_Rect*>* vSpritesSalto;
	std::vector<SDL_Rect*>* vSpritesCaida;
	std::vector<SDL_Rect*>* vSpritesEmpujar;

	// Iteradores de los vectores antes generados.
	int spriteQuieto;
	int spriteDesplazamiento;
	int spriteSalto;
	int spriteCaida;
	int spriteEmpujar;

	void crearSprites();

public:
	PersonajeVista(SDL_Renderer* r, Personaje* p);
	SDL_Texture* getVista();
	const SDL_Rect* getVentana();
	virtual ~PersonajeVista();
};

#endif /* PERSONAJEVISTA_H_ */
