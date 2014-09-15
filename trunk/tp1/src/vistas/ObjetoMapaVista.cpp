#include "ObjetoMapaVista.h"

ObjetoMapaVista::ObjetoMapaVista(ObjetoMapa* o){
	objeto = o;
}

SDL_Surface* ObjetoMapaVista::getVista(){
	std::vector<Pos>* vertices = objeto->getContorno();

	return nullptr;
}

ObjetoMapaVista::~ObjetoMapaVista() {
	// TODO Auto-generated destructor stub
}

