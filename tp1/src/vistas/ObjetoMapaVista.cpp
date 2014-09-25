#include "ObjetoMapaVista.h"
#include "../Constantes.h"
#include <SDL2/SDL2_gfxPrimitives.h>

ObjetoMapaVista::ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa* o) {
	objeto = o;
	this->setRenderer(r);
	ventana = new SDL_Rect();

	//Obtengo los vértices, transformando cada vertice en su simétrico respecto del eje Y
	std::vector<Pos*>* vertices = objeto->getContorno();
	for (unsigned i = 0; i < vertices->size(); i++) {
		vertices->at(i) = vertices->at(i)->ySimetrico();
	}

	int diametro;

	//Se calcula la superficie que puede llegar a ocupar dicho objeto, teniendo en cuenta
	//	las posibles rotaciones.
	if (objeto->esCirculo()) {
		Pos* pos = objeto->getPos()->ySimetrico();
		diametro = 2 * pos->getDistancia(vertices->at(0));
	}else {
		Pos *pIzqSup = getPosIzqSup(vertices);
		Pos *pDerInf = getPosDerInf(vertices);
		diametro = pIzqSup->getDistancia(pDerInf);
	}

	ventana->w = diametro;
	ventana->h = diametro;
}

/**
 * @return Se devuelve una textura, cuyo tamaño y posición se puede adquirir por medio del método
 * 			getVentana(). Observar que la textura debe ser liberada por el objeto que la recibe, ya
 * 			que se genera una textura por cada vez que se llama a este método.
 */
SDL_Texture* ObjetoMapaVista::getVista() {

	//Obtengo los vértices, transformando cada vertice en su simétrico respecto del eje Y
	std::vector<Pos*>* vertices = objeto->getContorno();
	for (unsigned i = 0; i < vertices->size(); i++) {
		vertices->at(i) = vertices->at(i)->ySimetrico();
	}

	int cantVertices = vertices->size();

	//Se crea la textura y sobre la cual se va a trabajar
	SDL_Texture* textura = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ventana->w, ventana->h);

	//En esta variable se guarda el punto sobre el cual se rotara la imagen
	SDL_Point* centro = new SDL_Point();

	//Se pone a la textura como target del render
	SDL_SetRenderTarget(renderer, textura);

	//Se pinta con pixeles transparentes a la textura
	SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Se dibuja la figura segun su tipo (taxonomía: circulo, no-circulo)
	//Si es circulo
	if (objeto->esCirculo()) {
		Pos* pos = objeto->getPos()->ySimetrico();
		int radio = pos->getDistancia(vertices->at(0));
		filledCircleColor(renderer, radio, radio, radio, 0xFF0000FF);
		filledCircleColor(renderer, radio, radio + radio / 2, radio / 4, 0xBBAA00FF);
		centro->x = radio;
		centro->y = radio;
	}
	//Si no es circulo
	else {
		short vx[cantVertices];
		short vy[cantVertices];
		Pos *pIzqSup = getPosIzqSup(vertices);
		for (int i = 0; i < cantVertices; i++) {
			vx[i] = vertices->at(i)->getX() - pIzqSup->getX();
			vy[i] = vertices->at(i)->getY() - pIzqSup->getY();
		}
		filledPolygonColor(renderer, vx, vy, cantVertices, 0xFF0000FF);
		Pos* posCentro = getPosCentro(vertices);
		centro->x = posCentro->getX();
		centro->y = posCentro->getY();
	}

	//Se modifica el target del renderer para que ahora apunte a la ventana (valor por defecto)
	SDL_SetRenderTarget(renderer, NULL);

	SDL_Texture* texturaRotada = this->rotar(textura, objeto->getRotacion(), centro);

	SDL_DestroyTexture(textura);

	return texturaRotada;
}

/**
 * @return SDL_Rect para obtener la posicion y el tamaño de la textura obtenida por el
 * 			método getVista(). Se devuelve un objeto de tipo "const" ya que no debe (ni se puede) modificar
 * 			su contenido, pero si puede consultarse.
 */
const SDL_Rect* ObjetoMapaVista::getVentana() {
	Pos* p = objeto->getPos()->ySimetrico();
	ventana->x = p->getX() - ventana->w / 2;
	ventana->y = p->getY() - ventana->h / 2;
	return ventana;
}

ObjetoMapaVista::~ObjetoMapaVista() {
	// TODO Auto-generated destructor stub
}

/*
 * @param	vPos vector de posiciones.
 * @return 	Posición (Xmin, Ymin), siendo Xmin el mínimo 'x'
 * 			dentro de entre todas posiciones que integran al vector vPos
 * 			y siendo Ymin el mínimo 'y' dentro de entre todas las posiciones
 * 			que integran al vector vPos.
 * 			Observar que Xmin, Ymin no tienen que pertenecer al mismo elemento
 * 			dentro del vector vPos.
 * @obs		Se llama getPosInzSup ya que en SDL el punto (0,0) u origen de
 * 			coordenadas se encuentra arriba a la izquierda
 */
Pos* ObjetoMapaVista::getPosIzqSup(std::vector<Pos*>* vPos) {
	Pos* p = vPos->at(0);
	int Xmin = p->getX();
	int Ymin = p->getY();
	for (unsigned i = 1; i < vPos->size(); i++) {
		p = vPos->at(i);
		if (p->getX() < Xmin)
			Xmin = p->getX();
		if (p->getY() < Ymin)
			Ymin = p->getY();
	}
	return new Pos(Xmin, Ymin);
}

/*
 * @param	vPos vector de posiciones.
 * @return 	Posición (Xmax, Ymax), siendo Xmax el maximo 'x'
 * 			dentro de entre todas posiciones que integran al vector vPos
 * 			y siendo Ymax el maximo 'y' dentro de entre todas las posiciones
 * 			que integran al vector vPos.
 * 			Observar que Xmax, Ymax no tienen que pertenecer al mismo elemento
 * 			dentro del vector vPos.
 * @obs		Se llama getPosDerInf ya que en SDL el punto (0,0) u origen de
 * 			coordenadas se encuentra arriba a la izquierda
 */
Pos* ObjetoMapaVista::getPosDerInf(std::vector<Pos*>* vPos) {
	Pos* p = vPos->at(0);
	int Xmax = p->getX();
	int Ymax = p->getY();
	for (unsigned i = 1; i < vPos->size(); i++) {
		p = vPos->at(i);
		if (p->getX() > Xmax)
			Xmax = p->getX();
		if (p->getY() > Ymax)
			Ymax = p->getY();
	}
	return new Pos(Xmax, Ymax);
}

Pos* ObjetoMapaVista::getPosCentro(std::vector<Pos*>* vPos){
	Pos* pIzqSup = getPosIzqSup(vPos);
	Pos* pDerInf = getPosDerInf(vPos);
	int x = pDerInf->getX() - pIzqSup->getX();
	int y = pDerInf->getY() - pIzqSup->getY();
	return new Pos(x,y);
}

/*
 *
 */
SDL_Texture* ObjetoMapaVista::rotar(SDL_Texture* t, float grados, SDL_Point* centro){
	//Se crea una textura donde se guardara la imagen rotada
	SDL_Texture* texturaRotada = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ventana->w, ventana->h);

	//Se pone a la textura como target del render
	SDL_SetRenderTarget(renderer, texturaRotada);

	//Se pinta con pixeles transparentes a la textura
	SDL_SetTextureBlendMode(texturaRotada, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Se rota la imagen
	SDL_RenderCopyEx(renderer, t, NULL, NULL, objeto->getRotacion(), centro, SDL_FLIP_NONE);

	//Se modifica el target del renderer para que ahora apunte a la ventana (valor por defecto)
	SDL_SetRenderTarget(renderer, NULL);

	return texturaRotada;
}
