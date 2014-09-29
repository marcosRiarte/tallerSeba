#ifndef CREADORDETEXTURAS_H_
#define CREADORDETEXTURAS_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../excepciones/SDL_Excepcion.h"
#include "../src/Constantes.h"


//Clase wrapper para texturas

class CreadorDeTexturas {
	private:
		//La textura SDL
		SDL_Texture* Textura;

		//Dimensiones de la imagen
		int Ancho;
		int Alto;

	public:
		//Inicializa las variables
		CreadorDeTexturas();

		//Carga la imagen desde un archivo
		bool cargarDesde( std::string rutaArchivo, SDL_Renderer* renderer);

		//borra la textura
		void free();

		//Setter del color
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Setter del blending
		void setBlend( SDL_BlendMode blending );

		//Setter de modulación alpha
		void setAlpha( Uint8 alpha );

		//Renderiza la textura en un punto dado
		void render( int x, int y, SDL_Rect* clip = nullptr, SDL_Renderer* renderer=nullptr);

		//Devuelve las dimensiones de la imagen
		int getAncho();
		int getAlto();


	virtual ~CreadorDeTexturas();
};

#endif /* CREADORDETEXTURAS_H_ */
