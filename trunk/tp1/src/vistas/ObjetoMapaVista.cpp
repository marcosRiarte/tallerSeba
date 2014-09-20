#include "ObjetoMapaVista.h"

ObjetoMapaVista::ObjetoMapaVista(ObjetoMapa* o){
	objeto = o;
}

SDL_Texture* ObjetoMapaVista::getVista(){
	std::vector<Pos*>* vertices = objeto->getContorno();
	//Si se trata de un circulo...
	if (vertices == nullptr){
	}
	return nullptr;
}

ObjetoMapaVista::~ObjetoMapaVista() {
	// TODO Auto-generated destructor stub
}

