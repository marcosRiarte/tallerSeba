#ifndef PERSONAJEVISTA_H_
#define PERSONAJEVISTA_H_

#include "Vista.h"
#include "../elementosJuego/personajes/Personaje.h"
#include <vector>

class PersonajeVista: public Vista {
private:
	Personaje personaje;
	Personaje::Estado estadoAnterior;

	// Texura que contiene todos los sprites que se van a usar
	static SDL_Texture* contenedorDeSprites;

	// Vectores con sprites que caracterizan cada accion
	static bool spritesCreados;
	static std::vector<SDL_Rect> vSpritesQuieto;
	static std::vector<SDL_Rect> vSpritesDesplazamiento;
	static std::vector<SDL_Rect> vSpritesSalto;
	static std::vector<SDL_Rect> vSpritesCaida;
	static std::vector<SDL_Rect> vSpritesEmpujar;

	// Iterador para los vectores de sprites
	int selectorDeSprite;

	SDL_Texture* crearContenedorDeSprites();
	void crearSprites();

	// Genera una textura, a partir de un vector de sprites y un selector
	void generarVista(SDL_Rect sprite, Personaje::E_PERFIL perfil);

	void setID();

public:
	PersonajeVista(SDL_Renderer* r, Personaje p);
	SDL_Texture* getVista();
	SDL_Rect getVentana();
	Pos getPos();
	void setPos(Pos posicion);
	void setEstado(Personaje::Estado estado);
	virtual ~PersonajeVista();
};

#endif /* PERSONAJEVISTA_H_ */
