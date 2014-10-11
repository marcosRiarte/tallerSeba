#ifndef PERSONAJEVISTA_H_
#define PERSONAJEVISTA_H_

#include "Vista.h"
#include "../elementosJuego/personajes/Personaje.h"

class PersonajeVista: public Vista {
private:
	Personaje* personaje;
	/*
	Personaje::Estado* estadoAnterior;
*/
	// Texura que contiene todos los sprites que se van a usar
	SDL_Texture* contenedorDeSprites;

	// Vectores con sprites que caracterizan cada accion
	std::vector<SDL_Rect*>* vSpritesQuieto;
	std::vector<SDL_Rect*>* vSpritesDesplazamiento;
	std::vector<SDL_Rect*>* vSpritesSalto;
	std::vector<SDL_Rect*>* vSpritesCaida;
	std::vector<SDL_Rect*>* vSpritesEmpujar;

	// Iterador para los vectores de sprites
	int selectorDeSprite;

	void cargarContenedorDeSprites();
	void crearSprites();

	// Genera una textura, a partir de un vector de sprites y un selector
	SDL_Texture* getVista(std::vector<SDL_Rect*>* sprites, int selector);

public:
	PersonajeVista(SDL_Renderer* r, Personaje* p);
	SDL_Texture* getVista();
	const SDL_Rect* getVentana();
	virtual ~PersonajeVista();
};

#endif /* PERSONAJEVISTA_H_ */
