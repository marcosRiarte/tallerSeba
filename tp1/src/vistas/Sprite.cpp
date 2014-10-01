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
	this->CaminandoDer = new std::vector<SDL_Rect*>();
	this->SaltandoDer = new std::vector<SDL_Rect*>();
	this->SaltandoDiagDer = new std::vector<SDL_Rect*>();
	this->Quieto = new std::vector<SDL_Rect*>();

	this->CaminandoIzq = new std::vector<SDL_Rect*>();
	this->SaltandoIzq = new std::vector<SDL_Rect*>();
	this->SaltandoDiagIzq = new std::vector<SDL_Rect*>();


	//Quieto
	this->Quieto->push_back(crearCuadro(165,87,48,50));

	//Izquierda

	//caminar
	this->CaminandoIzq->push_back(crearCuadro(38,16,22,24));
	this->CaminandoIzq->push_back(crearCuadro(62,16,20,24));
	this->CaminandoIzq->push_back(crearCuadro(94,16,18,24));

	//salto vertical
	this->SaltandoIzq->push_back(crearCuadro(118,10,21,30));

	//salto diagonal
	this->SaltandoDiagIzq->push_back(crearCuadro(150,16,23,25));
	this->SaltandoDiagIzq->push_back(crearCuadro(182,19,24,21));
	this->SaltandoDiagIzq->push_back(crearCuadro(216,16,21,24));
	this->SaltandoDiagIzq->push_back(crearCuadro(246,16,25,24));

	//Derecha

	//caminar
	this->CaminandoDer->push_back(crearCuadro(807,16,17,24));
	this->CaminandoDer->push_back(crearCuadro(780,16,20,24));
	this->CaminandoDer->push_back(crearCuadro(750,16,18,24));

	//salto vertical
	this->SaltandoDer->push_back(crearCuadro(723,10,21,30));

	//salto diagonal
	this->SaltandoDiagDer->push_back(crearCuadro(689,16,23,25));
	this->SaltandoDiagDer->push_back(crearCuadro(656,19,24,21));
	this->SaltandoDiagDer->push_back(crearCuadro(626,15,22,25));
	this->SaltandoDiagDer->push_back(crearCuadro(591,16,25,24));
}

std::vector<SDL_Rect*>* Sprite::listaDeCuadros(std::string tipoMov){
	if(tipoMov =="Quieto"){
		return this->Quieto;
	}

	if(tipoMov.compare("CaminandoIzq")==0){
		return CaminandoIzq;
	}
	if(tipoMov=="SaltandoIzq"){return SaltandoIzq;}
	if(tipoMov=="SaltandoDiagIzq"){return SaltandoDiagIzq;}
	if(tipoMov=="CaminandoDer"){return CaminandoDer;}
	if(tipoMov=="SaltandoDer"){return SaltandoDer;}
	if(tipoMov=="SaltandoDiagDer"){return SaltandoDiagDer;}
	return this->Quieto;
}



