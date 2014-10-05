#include "../vistas/Sprite.h"

SDL_Rect* crearCuadro(int x, int y, int w, int h){
	SDL_Rect* unCuadro = new SDL_Rect;
	unCuadro->x = x;
	unCuadro->y = y;
	unCuadro->w = w;
	unCuadro->h = h;
	return unCuadro;
}

Sprite::Sprite(){
	this->CayendoDer = new std::vector<SDL_Rect*>();
	this->SaltandoDer = new std::vector<SDL_Rect*>();
	this->CaminandoDer = new std::vector<SDL_Rect*>();
	this->Quieto = new std::vector<SDL_Rect*>();

	this->CaminandoIzq = new std::vector<SDL_Rect*>();
	this->SaltandoIzq = new std::vector<SDL_Rect*>();
	this->CayendoIzq = new std::vector<SDL_Rect*>();


	//Quieto
	this->Quieto->push_back(crearCuadro(165,87,48,50));
	this->Quieto->push_back(crearCuadro(165,87,48,50));
	this->Quieto->push_back(crearCuadro(165,87,48,50));
	this->Quieto->push_back(crearCuadro(165,87,48,50));

	//Izquierda

	//caminar
	this->CaminandoIzq->push_back(crearCuadro(38,16,22,24));
	this->CaminandoIzq->push_back(crearCuadro(62,16,20,24));
	this->CaminandoIzq->push_back(crearCuadro(94,16,18,24));
	this->CaminandoIzq->push_back(crearCuadro(38,16,22,24));

	//salto vertical
	this->CayendoIzq->push_back(crearCuadro(118,10,20,30));
	this->CayendoIzq->push_back(crearCuadro(118,10,20,30));
	this->CayendoIzq->push_back(crearCuadro(118,10,20,30));
	this->CayendoIzq->push_back(crearCuadro(118,10,20,30));

	//salto diagonal
	this->SaltandoIzq->push_back(crearCuadro(150,16,23,25));
	this->SaltandoIzq->push_back(crearCuadro(182,19,22,21));
	this->SaltandoIzq->push_back(crearCuadro(216,16,21,24));
	this->SaltandoIzq->push_back(crearCuadro(246,16,25,24));

	//Derecha

	//caminar
	this->CaminandoDer->push_back(crearCuadro(807,16,17,24));
	this->CaminandoDer->push_back(crearCuadro(780,16,20,24));
	this->CaminandoDer->push_back(crearCuadro(750,16,18,24));
	this->CaminandoDer->push_back(crearCuadro(807,16,17,24));

	//salto vertical
	this->CayendoDer->push_back(crearCuadro(723,10,20,30));
	this->CayendoDer->push_back(crearCuadro(723,10,20,30));
	this->CayendoDer->push_back(crearCuadro(723,10,20,30));
	this->CayendoDer->push_back(crearCuadro(723,10,20,30));

	//salto diagonal
	this->SaltandoDer->push_back(crearCuadro(689,16,23,25));
	this->SaltandoDer->push_back(crearCuadro(656,19,22,21));
	this->SaltandoDer->push_back(crearCuadro(626,15,22,25));
	this->SaltandoDer->push_back(crearCuadro(591,16,25,24));
}

std::vector<SDL_Rect*>* Sprite::listaDeCuadros(std::string tipoMov){

	if(tipoMov=="CaminandoIzq"){return CaminandoIzq;}
	if(tipoMov=="SaltandoIzq"){return SaltandoIzq;}
	if(tipoMov=="CayendoIzq"){return CayendoIzq;}
	if(tipoMov=="CaminandoDer"){return CaminandoDer;}
	if(tipoMov=="SaltandoDer"){return SaltandoDer;}
	if(tipoMov=="CayendoDer"){return CayendoDer;}
	return this->Quieto;
}



