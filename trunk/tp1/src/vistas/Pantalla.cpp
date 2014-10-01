#include <iostream>
#include <string>
#include "../Constantes.h"
#include "Pantalla.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>

Pantalla::Pantalla(Config* config) {
	this->altoPx = config->getAltoPx();
	this->anchoPx = config->getAnchoPx();
	this->alto = config->getAlto();
	this->ancho = config->getAncho();
	this->numeroDeCuadro = 0;
	this->dirImg = config->getFondo();
	this->vistas = nullptr;
	this->ventana = nullptr;
	this->renderer = nullptr;
	this->fondo = nullptr;
	this->unSprite = nullptr;
	this->listaDeCuadros = new std::vector<SDL_Rect*>();
	this->HojaDeSpritesDeTextura= new CreadorDeTexturas();
	this->config = config;
	inicializar();
	this->agregarVistas(config->getObjetos(),config->getPersonajes());
}

/**
 * obs		Necesita que SDL este iniciado.
 */
void Pantalla::inicializar() throw (SDL_Excepcion){
	ventana = SDL_CreateWindow("SnowBross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, anchoPx, altoPx, SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		loguer->loguear("No se pudo crear la ventana principal", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando ventana principal: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}
	renderer =  SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr){
		loguer->loguear("No se pudo crear el renderer", Log::LOG_ERR);
		const char* msg = ((std::string)"Error creando el renderer: ").append(SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}

	//Paso a const char* el string del nombre de la imagen.
			const char* dirFondo = dirImg.c_str();

	this->fondo = IMG_LoadTexture(renderer, dirFondo);
	if (fondo == nullptr) {
		loguer->loguear("No se encontró imagen de fondo", Log::LOG_ERR);
		const char* msg =
				((std::string) "Error cargando el fondo de pantalla: ").append(
						SDL_GetError()).c_str();
		throw new SDL_Excepcion(msg);
	}

	//Cargar texturas del sprite.
	if (!HojaDeSpritesDeTextura->cargarDesde("img/SnowSprite.bmp",renderer)) {
		std::string errorTextura = "Imposible cargar la textura desde img/SnowSprite.bmp";
					const char* errorCargaTextura = errorTextura.c_str();
							loguer->loguear(errorCargaTextura,Log::LOG_ERR);
	} else {
		unSprite = new Sprite();
	}
}

SDL_Renderer* Pantalla::getRenderer(){
	return renderer;
}

void Pantalla::agregarVistas(std::vector<ObjetoMapa*>* objetos, std::vector<Personaje*>* personajes){
	vistas = new std::vector<Vista*>;
	Vista* v;
	for(unsigned i = 0; i < objetos->size(); i++){
		v = new ObjetoMapaVista(renderer, objetos->at(i));
		vistas->push_back(v);
	}

	for(unsigned i = 0; i < personajes->size(); i++){
			v = new ObjetoMapaVista(renderer, personajes->at(i)->getRectangulo());
			vistas->push_back(v);
		}
}


void Pantalla::cambiar(){
	//Limpio la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//Cargo el fondo de pantalla
	SDL_RenderCopy(renderer, fondo, NULL, NULL);


	//Se cargan los objetos
	for(unsigned i = 0; i < vistas->size()-1; i++ ){
		Vista* vista = vistas->at(i);
		//obtengo la imagen ya rotada con el tamanio en dimensiones Box2D
		SDL_Texture* textura = vista->getVista();

		//La imprimo en la pantalla con la debida transformacion
		SDL_Rect* r = new SDL_Rect();
		r->h = vista->getVentana()->h*altoPx/alto;
		r->w = vista->getVentana()->w*anchoPx/ancho;
		r->x = vista->getVentana()->x*anchoPx/ancho;
		r->y = vista->getVentana()->y*altoPx/alto;
		SDL_RenderCopy(renderer, textura, NULL, r);
		SDL_DestroyTexture(textura);
	}

	//Se carga el objeto personaje
	Vista* unaVista = vistas->at(vistas->size()-1);

	//"CayendoIzq","SaltandoIzq"),,"CaminandoIzq","CayendoDer","SaltandoDer","CaminandoDer","Quieto"

	this->listaDeCuadros = unSprite->listaDeCuadros("Quieto");
	if(config->getPersonajes()->at(0)->getEstado()=="Quieto"){
		this->listaDeCuadros = unSprite->listaDeCuadros("Quieto");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CayendoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CayendoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="SaltandoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("SaltandoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CaminandoIzq"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CaminandoIzq");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CayendoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CayendoDer");
	}else if(config->getPersonajes()->at(0)->getEstado()=="SaltandoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("SaltandoDer");
	}else if(config->getPersonajes()->at(0)->getEstado()=="CaminandoDer"){
		this->listaDeCuadros = unSprite->listaDeCuadros("CaminandoDer");
	}
	//Renderizamos el sprite

	std::cout << "tamanio lista de cuadros" << listaDeCuadros->size() << "\n";
	std::cout << "numerode cuadros " << numeroDeCuadro << "\n";
	SDL_Rect* cuadroActual = listaDeCuadros->at((numeroDeCuadro)/(listaDeCuadros->size()));
	HojaDeSpritesDeTextura->render((unaVista->getVentana()->x),(unaVista->getVentana()->y), cuadroActual, renderer);

	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);

	//Siguiente cuadro
	++numeroDeCuadro;
	//Ciclado de la animación
	if ((numeroDeCuadro / listaDeCuadros->size()) >= (listaDeCuadros->size())) {
		numeroDeCuadro = 0;
	}

}


int Pantalla::getAlto() {
	return alto;
}
int Pantalla::getAncho(){
	return ancho;
}

Pantalla::~Pantalla() {}

