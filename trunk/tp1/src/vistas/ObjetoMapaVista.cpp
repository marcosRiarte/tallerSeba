#include "ObjetoMapaVista.h"
#include "../Constantes.h"
#include <SDL2/SDL2_gfxPrimitives.h>

/*
 * TODO Hay que pensar que pasa cuando se trata de un círculo
 */
ObjetoMapaVista::ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa* o) {
	objeto = o;
	this->setRenderer(r);
	ventana = new SDL_Rect();
	std::vector<Pos*>* vertices = objeto->getContorno();
	//Se calcula la superficie que va a ocupa dicho objeto
	if (objeto->esCirculo()){
		Pos* pos = objeto->getPos();
		Pos* posAux = new Pos(pos->getX() - vertices->at(0)->getX(), pos->getY() - vertices->at(0)->getY());
		int radio = posAux->getNorma();
		ventana->w = 2*radio;
		ventana->h = 2*radio;
	}
	else{
		Pos *pIzqSup = getPosIzqSup(vertices);
		Pos *pDerInf = getPosDerInf(vertices);
		ventana->w = pDerInf->getX() - pIzqSup->getX();
		ventana->h = pDerInf->getY() - pIzqSup->getY();
	}
}

/**
 * @return Se devuelve una textura, cuyo tamaño y posición se puede adquirir por medio del método
 * 			getVentana(). Observar que la textura debe ser liberada por el objeto que la recibe, ya
 * 			que se genera una textura por cada vez que se llama a este método.
 */
SDL_Texture* ObjetoMapaVista::getVista(){
	std::vector<Pos*>* vertices = objeto->getContorno();
	int cantVertices = vertices->size();

	//Se crea la textura y sobre la cual se va a trabajar
	SDL_Texture* textura = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN,	SDL_TEXTUREACCESS_TARGET, ventana->w, ventana->h);

	//Se pone a la textura como target del render
	SDL_SetRenderTarget(renderer, textura);

	//Se pinta con pixeles transparentes a la textura
	SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Se dibuja la figura segun su tipo (taxonomía: circulo, no-circulo)
	//Si es circulo
	if (objeto->esCirculo()){
		Pos* pos = objeto->getPos();
		Pos* posAux = new Pos(pos->getX() - vertices->at(0)->getX(), pos->getY() - vertices->at(0)->getY());
		int radio = posAux->getNorma();
		filledCircleColor(renderer, pos->getX(), -pos->getY(), radio, 0xFFAA00FF);
		filledCircleColor(renderer, pos->getX(), -pos->getY() + radio/2, radio/4, 0xFF0000FF);
	}
	//Si no es circulo
	else{
		short vx[cantVertices];
		short vy[cantVertices];
		Pos *pIzqSup = getPosIzqSup(vertices);
		for (int i = 0; i < cantVertices; i++) {
			vx[i] = vertices->at(i)->getX() - pIzqSup->getX();
			vy[i] = -vertices->at(i)->getY() - pIzqSup->getY();
		}
		filledPolygonColor(renderer, vx, vy, cantVertices, 0xFF0000FF);
	}
	//Se modifica el target del renderer para que ahora apunte a la ventana (valor por defecto)
	SDL_SetRenderTarget(renderer, NULL);
	return textura;
}

/**
 * @return Se devuelve un SDL_Rect para obtener la posicion y el tamaño de la textura obtenida por el
 * 			método getVista(). Se devuelve un objeto de tipo "const" ya que no debe (ni se puede) modificar
 * 			su contenido, pero si puede consultarse.
 */
const SDL_Rect* ObjetoMapaVista::getVentana(){
	ventana->x = objeto->getPos()->getX();
	ventana->y = -objeto->getPos()->getY();
	return ventana;
}

ObjetoMapaVista::~ObjetoMapaVista() {
	// TODO Auto-generated destructor stub
}

/*
 * @param	vPos vector de posiciones.
 * @return 	Devuelve el una posición (Xmin, Ymin), siendo Xmin el mínimo 'x'
 * 			dentro de entre todas posiciones que integran al vector vPos
 * 			y siendo Ymin el mínimo 'y' dentro de entre todas las posiciones
 * 			que integran al vector vPos.
 * 			Observar que Xmin, Ymin no tienen que pertenecer al mismo elemento
 * 			dentro del vector vPos.
 * @obs		Se llama getPosInzSup ya que en SDL el punto (0,0) u origen de
 * 			coordenadas se encuentra arriba a la izquierda
 */
Pos* ObjetoMapaVista::getPosIzqSup(std::vector<Pos*>* vPos){
	Pos* p = vPos->at(0);
	int Xmin = p->getX();
	int Ymin = -p->getY();
	for(unsigned i = 1; i < vPos->size(); i++){
		p = vPos->at(i);
		if (p->getX() < Xmin)
			Xmin= p->getX();
		if (-p->getY() < Ymin)
			Ymin= -p->getY();
	}
	return new Pos(Xmin, Ymin);
}

/*
 * @param	vPos vector de posiciones.
 * @return 	Devuelve el una posición (Xmax, Ymax), siendo Xmax el maximo 'x'
 * 			dentro de entre todas posiciones que integran al vector vPos
 * 			y siendo Ymax el maximo 'y' dentro de entre todas las posiciones
 * 			que integran al vector vPos.
 * 			Observar que Xmax, Ymax no tienen que pertenecer al mismo elemento
 * 			dentro del vector vPos.
 * @obs		Se llama getPosDerInf ya que en SDL el punto (0,0) u origen de
 * 			coordenadas se encuentra arriba a la izquierda
 */
Pos* ObjetoMapaVista::getPosDerInf(std::vector<Pos*>* vPos){
	Pos* p = vPos->at(0);
	int Xmax = p->getX();
	int Ymax = -p->getY();
	for(unsigned i = 1; i < vPos->size(); i++){
		p = vPos->at(i);
		if (p->getX() > Xmax)
			Xmax= p->getX();
		if (-p->getY() > Ymax)
			Ymax= -p->getY();
	}
	return new Pos(Xmax, Ymax);
}
