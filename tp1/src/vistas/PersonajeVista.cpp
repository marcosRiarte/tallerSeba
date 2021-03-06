#include <SDL2/SDL_image.h>
#include "PersonajeVista.h"
#include "../Constantes.h"

#define PATH_IMAGEN_SPRITES					"img/SpritesPersonaje.png"
#define ANCHO_PX_SPRITE						125
#define ALTO_PX_SPRITE						250
#define CANTIDAD_SPRITES_QUIETO				1
#define CANTIDAD_SPRITES_DESPLAZAMIENTO		3
#define CANTIDAD_SPRITES_SALTO				5
#define CANTIDAD_SPRITES_CAIDA				1
#define CANTIDAD_SPRITES_EMPUJAR			3


PersonajeVista::PersonajeVista(SDL_Renderer* r, Personaje* p) {
	renderer = r;
	personaje = p;
	ventana = SDL_Rect();
	ventana.h = personaje->getAlto();
	ventana.w = personaje->getAncho();

	estadoAnterior = Personaje::Estado();
	estadoAnterior.perfil = Personaje::IZQUIERDA;
	estadoAnterior.accion = Personaje::QUIETO;

	vSpritesQuieto = std::vector<SDL_Rect>();
	vSpritesDesplazamiento = std::vector<SDL_Rect>();
	vSpritesSalto = std::vector<SDL_Rect>();
	vSpritesCaida = std::vector<SDL_Rect>();
	vSpritesEmpujar = std::vector<SDL_Rect>();

	selectorDeSprite = 0;

	textura = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ventana.w, ventana.h);

	cargarContenedorDeSprites();
	crearSprites();

}

/**
 * \brief
 */
void PersonajeVista::cargarContenedorDeSprites(){
	SDL_Surface* superficie = IMG_Load(PATH_IMAGEN_SPRITES);
	SDL_SetColorKey( superficie, SDL_TRUE, SDL_MapRGB( superficie->format, 255, 255, 255 ) );
	this->contenedorDeSprites = SDL_CreateTextureFromSurface(renderer, superficie);
	SDL_FreeSurface(superficie);
}

/**
 * \brief	Carga los vectores que contienen los sprites para cada tipo de movimiento que realiza el personaje.
 * 			Llena cada vector con elementos del tipo SDL_Rect, que gestionan informaci�n acerca de qu� porci�n de
 * 			la imagen que possee todos los sprites(\rutaImagenConSprites la referencia) se debe tener en cuenta.
 */
void PersonajeVista::crearSprites(){

	//Sprite cuando esta quieto
	for (int i = 0; i < CANTIDAD_SPRITES_QUIETO; i++) {
		SDL_Rect sprite = SDL_Rect();
		sprite.h = ALTO_PX_SPRITE;
		sprite.w = ANCHO_PX_SPRITE;
		sprite.x = i * ANCHO_PX_SPRITE;
		sprite.y = 0;
		vSpritesQuieto.push_back(sprite);
	}

	//Sprites cuando hay desplazamiento
	for (int i = 0; i < CANTIDAD_SPRITES_DESPLAZAMIENTO; i++) {
		SDL_Rect sprite = SDL_Rect();
		sprite.h = ALTO_PX_SPRITE;
		sprite.w = ANCHO_PX_SPRITE;
		sprite.x = i * ANCHO_PX_SPRITE;
		sprite.y = ALTO_PX_SPRITE;
		vSpritesDesplazamiento.push_back(sprite);
	}

	//Sprites cuando salta
	for (int i = 0; i < CANTIDAD_SPRITES_SALTO; i++) {
		SDL_Rect sprite = SDL_Rect();
		sprite.h = ALTO_PX_SPRITE;
		sprite.w = ANCHO_PX_SPRITE;
		sprite.x = i * ANCHO_PX_SPRITE;
		sprite.y = 2 * ALTO_PX_SPRITE;
		vSpritesSalto.push_back(sprite);
	}

	//Sprites cuando cae
	for (int i = 0; i < CANTIDAD_SPRITES_CAIDA; i++) {
		SDL_Rect sprite = SDL_Rect();
		sprite.h = ALTO_PX_SPRITE;
		sprite.w = ANCHO_PX_SPRITE;
		sprite.x = i * ANCHO_PX_SPRITE;
		sprite.y = 2 * ALTO_PX_SPRITE;
		vSpritesCaida.push_back(sprite);
	}

	//Sprites cuando empuja
	for (int i = 0; i < CANTIDAD_SPRITES_EMPUJAR; i++) {
		SDL_Rect sprite = SDL_Rect();
		sprite.h = ALTO_PX_SPRITE;
		sprite.w = ANCHO_PX_SPRITE;
		sprite.x = i * ANCHO_PX_SPRITE;
		sprite.y = 3 * ALTO_PX_SPRITE;
		vSpritesEmpujar.push_back(sprite);
	}

}

SDL_Texture* PersonajeVista::getVista() {
	Personaje::Estado estadoActual = personaje->getEstado();

	if (estadoActual.accion == estadoAnterior.accion)
		selectorDeSprite++;

	switch(estadoActual.accion){
		case(Personaje::E_ACCION::QUIETO):
			selectorDeSprite = selectorDeSprite % (CANTIDAD_SPRITES_QUIETO * FRAME_RATE);
			generarVista(vSpritesQuieto.at(selectorDeSprite / FRAME_RATE), estadoActual.perfil);
			break;
		case(Personaje::E_ACCION::DESPLAZANDO):
			selectorDeSprite = selectorDeSprite % (CANTIDAD_SPRITES_DESPLAZAMIENTO * FRAME_RATE);
			generarVista(vSpritesDesplazamiento.at(selectorDeSprite / FRAME_RATE), estadoActual.perfil);
			break;
		case(Personaje::E_ACCION::SALTANDO):
			selectorDeSprite = selectorDeSprite % (CANTIDAD_SPRITES_SALTO * FRAME_RATE);
			generarVista(vSpritesSalto.at(selectorDeSprite / FRAME_RATE), estadoActual.perfil);
			break;
		case(Personaje::E_ACCION::CAYENDO):
			selectorDeSprite = selectorDeSprite % (CANTIDAD_SPRITES_CAIDA * FRAME_RATE);
			generarVista(vSpritesCaida.at(selectorDeSprite / FRAME_RATE), estadoActual.perfil);
			break;
		case(Personaje::E_ACCION::EMPUJANDO):
			selectorDeSprite = selectorDeSprite % (CANTIDAD_SPRITES_EMPUJAR * FRAME_RATE);
			generarVista(vSpritesEmpujar.at(selectorDeSprite / FRAME_RATE), estadoActual.perfil);
			break;
		default:
			throw;
	}
	estadoAnterior.perfil = estadoActual.perfil;
	estadoAnterior.accion = estadoActual.accion;
	return textura;
}

void PersonajeVista::generarVista(SDL_Rect sprite, Personaje::E_PERFIL perfil) {
	SDL_SetRenderTarget(renderer, textura);
	SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	if (perfil == Personaje::DERECHA)
		SDL_RenderCopyEx(renderer, contenedorDeSprites, &sprite, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(renderer, contenedorDeSprites, &sprite, NULL);
	SDL_SetRenderTarget(renderer, NULL);
}

const SDL_Rect PersonajeVista::getVentana() {
	Pos p = personaje->getPos().ySimetrico();
	ventana.x = p.getX() - ventana.w / 2;
	ventana.y = p.getY() - ventana.h / 2;
	return ventana;
}

PersonajeVista::~PersonajeVista() {
	SDL_DestroyTexture(textura);
	SDL_DestroyTexture(contenedorDeSprites);
}

