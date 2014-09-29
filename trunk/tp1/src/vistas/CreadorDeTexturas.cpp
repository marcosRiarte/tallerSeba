#include "CreadorDeTexturas.h"
#include <iostream>

CreadorDeTexturas::CreadorDeTexturas() {
	//Initialize
	Textura = nullptr;
	Ancho = 0;
	Alto = 0;
}

bool CreadorDeTexturas::cargarDesde( std::string rutaArchivo, SDL_Renderer* renderer){
	//Elimina la textura pre-existente
	free();

	//La textura final
	SDL_Texture* nuevaTextura = nullptr;

	//Carga la imagen desde la ruta especificada
	SDL_Surface* Superficie = IMG_Load( rutaArchivo.c_str() );
	if( Superficie == nullptr )
	{
		std::string errorCarga = "Imposible cargar la imagen "+rutaArchivo+" SDL Error: "+SDL_GetError();

		const char* errorCargaImagen = errorCarga.c_str();

		loguer->loguear(errorCargaImagen,Log::LOG_ERR);
				throw new SDL_Excepcion(errorCargaImagen);
	}
	else
	{
		//Seteo del color
		SDL_SetColorKey( Superficie, SDL_TRUE, SDL_MapRGB( Superficie->format, 255, 0, 255 ) );

		//Crear textura sobre la superficie
		nuevaTextura = SDL_CreateTextureFromSurface( renderer, Superficie );
		if( nuevaTextura == nullptr )
		{
			std::string errorTextura = "Imposible cargar la textura desde "+rutaArchivo+" Error SDL: "+SDL_GetError();
			const char* errorCargaTextura = errorTextura.c_str();
					loguer->loguear(errorCargaTextura,Log::LOG_ERR);
							throw new SDL_Excepcion(errorCargaTextura);
		}
		else
		{
			//seteo de las dimensiones que va a ocupar
			Ancho = Superficie->w;
			Alto = Superficie->h;
		}

		//Elimina la superficie cargada
		SDL_FreeSurface( Superficie );
	}

	//Si fue exitosa la creación de la textura devuelve true
	Textura = nuevaTextura;
	return Textura != nullptr;
}

void CreadorDeTexturas::free(){
	//Libera la textura si existe
	if( Textura != nullptr )
	{
		SDL_DestroyTexture( Textura );
		Textura = nullptr;
		Ancho = 0;
		Alto = 0;
	}
}

void CreadorDeTexturas::setColor( Uint8 rojo, Uint8 verde, Uint8 azul ){
	//Setea el RGB de la textura
	SDL_SetTextureColorMod( Textura, rojo, verde, azul );
}

void CreadorDeTexturas::setBlend( SDL_BlendMode blending ){
	//Setea la función de blending
	SDL_SetTextureBlendMode( Textura, blending );
}

void CreadorDeTexturas::setAlpha( Uint8 alpha ){
	//Modula el alpha de la textura
	SDL_SetTextureAlphaMod( Textura, alpha );
}

void CreadorDeTexturas::render( int x, int y, SDL_Rect* fotograma,SDL_Renderer* render ){
	//Se pide memoria para la imagen a ser dibujada
	SDL_Rect* unRender = new SDL_Rect();

	//Seteo de las dimensiones del renderizado del cuadro
	if( fotograma != nullptr )
	{
		unRender->h = fotograma->h;
		unRender->w = fotograma->w;
		unRender->x = 100;
		unRender->y = 80;
	}

	//Se dibuja en pantalla
	SDL_RenderCopy( render, Textura, fotograma, unRender );
}

int CreadorDeTexturas::getAncho(){
	return Ancho;
}

int CreadorDeTexturas::getAlto(){
	return Alto;
}
CreadorDeTexturas::~CreadorDeTexturas(){
	free();
}

