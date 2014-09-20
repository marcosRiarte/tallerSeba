#include "ObjetoMapaVista.h"
#include "../Constantes.h"
#include <SDL2/SDL2_gfxPrimitives.h>

ObjetoMapaVista::ObjetoMapaVista(ObjetoMapa* o){
	objeto = o;
}

SDL_Surface* ObjetoMapaVista::getVista(){
	std::vector<Pos*>* vertices = objeto->getContorno();
	int cantVertices = vertices->size();
	//Se calcula la superficie que va a ocupa dicho objeto
	Pos *pIzqSup = getPosIzqSup(vertices);
	Pos *pDerInf = getPosDerInf(vertices);
	int ancho = pDerInf->getX() - pIzqSup->getX();
	int alto = pIzqSup->getY() - pDerInf->getY()  ;
	//Se crea la superficie y el renderer que va a trabajar sobre ella
	SDL_Surface * sup = SDL_CreateRGBSurface(0, ancho, alto, 32, rmask, gmask, bmask, amask);
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(sup);
	//Se dibuja la figura
	short vx[cantVertices];
	short vy[cantVertices];
	for(int i = 0; i < cantVertices; i++){
		vx[i] = vertices->at(i)->getX();
		vy[i] = vertices->at(i)->getY();
	}
	filledPolygonColor(renderer, vx, vy, cantVertices, 0xAABB0000);
	return sup;
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
	int s = vPos->size();
	int oiadf = s;
	for(unsigned int i = 1; i < vPos->size(); i++){
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
	for(unsigned int i = 1; i < vPos->size(); i++){
		p = vPos->at(i);
		if (p->getX() > Xmax)
			Xmax= p->getX();
		if (-p->getY() > Ymax)
			Ymax= -p->getY();
	}
	return new Pos(Xmax, Ymax);
}
