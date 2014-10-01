#include "PersonajeVista.h"
#include <SDL2/SDL_image.h>

#define PATH_IMAGEN_SPRITES					"../../img/SpritesPersonaje.png"
#define ANCHO_PX_SPRITE						125
#define ALTO_PX_SPRITE						250
#define CANTIDAD_SPRITES_QUIETO				1
#define CANTIDAD_SPRITES_DESPLAZAMIENTO		3
#define CANTIDAD_SPRITES_SALTO				5
#define CANTIDAD_SPRITES_CAIDA				1
#define CANTIDAD_SPRITES_EMPUJAR			3

/*
PersonajeVista::PersonajeVista(SDL_Renderer* r, Personaje* p) {
	renderer = r;
	personaje = p;
	ventana->h = personaje->getAlto();
	ventana->w = personaje->getAncho();
/*TODO
	estadoAnterior = new Personaje::Estado();
	estadoAnterior->perfil = Personaje::IZQUIERDA;
	estadoAnterior->accion = Personaje::QUIETO;
*/
/*
	vSpritesQuieto = new std::vector<SDL_Rect*>;
	vSpritesDesplazamiento = new std::vector<SDL_Rect*>;
	vSpritesSalto = new std::vector<SDL_Rect*>;
	vSpritesCaida = new std::vector<SDL_Rect*>;
	vSpritesEmpujar = new std::vector<SDL_Rect*>;

	selectorDeSprite = 0;

	cargarContenedorDeSprites();
	crearSprites();

}

/**
 * \brief
 */
/*
void PersonajeVista::cargarContenedorDeSprites(){
	SDL_Surface* superficie = IMG_Load(PATH_IMAGEN_SPRITES);
	this->contenedorDeSprites = SDL_CreateTextureFromSurface(renderer, superficie);
	SDL_free(superficie);

	/**
	 * Esto que viene ahora solo sirve a modo de prueba para ver como es que carga la imagen
	 * 	contenedora de sprites
	 */
/*
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		//Cargo el fondo de pantalla
		SDL_RenderCopy(renderer, contenedorDeSprites, NULL, NULL);
		SDL_RenderPresent(renderer);
	/*
	 * TODO verificar si el color key esta bien puesto
	 * TODO ver que pasa con los tamaños.
	 */
/*
}

/**
 * \brief	Carga los vectores que contienen los sprites para cada tipo de movimiento que realiza el personaje.
 * 			Llena cada vector con elementos del tipo SDL_Rect, que gestionan información acerca de qué porción de
 * 			la imagen que possee todos los sprites(\rutaImagenConSprites la referencia) se debe tener en cuenta.
 */
/*
void PersonajeVista::crearSprites(){

	//Sprite cuando esta quieto
	for (int i = 0; i < CANTIDAD_SPRITES_QUIETO; i++) {
		SDL_Rect* sprite = new SDL_Rect();
		sprite->h = ALTO_PX_SPRITE;
		sprite->w = ANCHO_PX_SPRITE;
		sprite->x = i * ANCHO_PX_SPRITE;
		sprite->y = 0;
		vSpritesQuieto->push_back(sprite);
	}

	//Sprites cuando hay desplazamiento
	for (int i = 0; i < CANTIDAD_SPRITES_DESPLAZAMIENTO; i++) {
		SDL_Rect* sprite = new SDL_Rect();
		sprite->h = ALTO_PX_SPRITE;
		sprite->w = ANCHO_PX_SPRITE;
		sprite->x = i * ANCHO_PX_SPRITE;
		sprite->y = ALTO_PX_SPRITE;
		vSpritesDesplazamiento->push_back(sprite);
	}

	//Sprites cuando salta
	for (int i = 0; i < CANTIDAD_SPRITES_SALTO; i++) {
		SDL_Rect* sprite = new SDL_Rect();
		sprite->h = ALTO_PX_SPRITE;
		sprite->w = ANCHO_PX_SPRITE;
		sprite->x = i * ANCHO_PX_SPRITE;
		sprite->y = 2 * ALTO_PX_SPRITE;
		vSpritesSalto->push_back(sprite);
	}

	//Sprites cuando cae
	for (int i = 0; i < CANTIDAD_SPRITES_CAIDA; i++) {
		SDL_Rect* sprite = new SDL_Rect();
		sprite->h = ALTO_PX_SPRITE;
		sprite->w = ANCHO_PX_SPRITE;
		sprite->x = i * ANCHO_PX_SPRITE;
		sprite->y = 3 * ALTO_PX_SPRITE;
		vSpritesCaida->push_back(sprite);
	}

	//Sprites cuando empuja
	for (int i = 0; i < CANTIDAD_SPRITES_EMPUJAR; i++) {
		SDL_Rect* sprite = new SDL_Rect();
		sprite->h = ALTO_PX_SPRITE;
		sprite->w = ANCHO_PX_SPRITE;
		sprite->x = i * ANCHO_PX_SPRITE;
		sprite->y = 4 * ALTO_PX_SPRITE;
		vSpritesEmpujar->push_back(sprite);
	}

}

/*
SDL_Texture* PersonajeVista::getVista() {
	SDL_Texture* textura;
	/*
	Personaje::Estado estadoActual = personaje->getEstado();

	if (estadoActual.accion == estadoAnterior->accion)
		selectorDeSprite++;

	switch(estadoActual.accion){
		case(Personaje::E_ACCION::QUIETO):
			textura = getVista(vSpritesQuieto, selectorDeSprite);
			break;
		case(Personaje::E_ACCION::DESPLAZANDO):
			textura = getVista(vSpritesDesplazamiento, selectorDeSprite);
			break;
		case(Personaje::E_ACCION::SALTANDO):
			textura = getVista(vSpritesSalto, selectorDeSprite);
			break;
		case(Personaje::E_ACCION::CAYENDO):
			textura = getVista(vSpritesCaida, selectorDeSprite);
			break;
		case(Personaje::E_ACCION::EMPUJANDO):
			textura = getVista(vSpritesEmpujar,selectorDeSprite);
			break;
		default:
			throw;
	}
	estadoAnterior->perfil = estadoActual.perfil;
	estadoAnterior->accion = estadoActual.accion;
	return textura;
}

/**
 * TODO una vez que esté cargada la imagen principal con todos los sprites en ella,
 * 	y testeado (importante) hay que hacer esto.
 */

	/*
SDL_Texture* PersonajeVista::getVista(std::vector<SDL_Rect*>* sprites, int iterador){
	return nullptr;
}

const SDL_Rect* PersonajeVista::getVentana() {
	Pos* p = personaje->getPosicion()->ySimetrico();
	ventana->x = p->getX() - ventana->w / 2;
	ventana->y = p->getY() - ventana->h / 2;
	return ventana;
}

PersonajeVista::~PersonajeVista() {
	// TODO Auto-generated destructor stub
}

*/
