#include "ObjetoMapaVista.h"
#include "../Constantes.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>
#include <iostream>

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
		delete pos;
	}else {
		Pos *pIzqSup = getPosIzqSup(vertices);
		Pos *pDerInf = getPosDerInf(vertices);
		diametro = pIzqSup->getDistancia(pDerInf);
		delete pIzqSup;
		delete pDerInf;
	}
	ventana->w = diametro;
	ventana->h = diametro;
}

void liberarVertices(std::vector <Pos*> & a){
   for ( unsigned i = 0; i < a.size(); i++ ) {
      delete a[i];
   }
   a.clear();
}

/**
 * \return	Textura, cuyo tamaño y posición se puede adquirir por medio del método
 * 			getVentana(). Observar que la textura debe ser liberada por el objeto que la recibe, ya
 * 			que se genera una textura por cada vez que se llama a este método.
 */
SDL_Texture* ObjetoMapaVista::getVista() {

	long color = ( objeto->getColor() ) + 0xFF000000;

	//Obtengo los vértices, transformando cada vertice en su simétrico respecto del eje Y
	std::vector<Pos*>* vertices = objeto->getContorno();
	for (unsigned i = 0; i < vertices->size(); i++) {
		vertices->at(i) = vertices->at(i)->ySimetrico();
	}

	int cantVertices = vertices->size();

	//Se crea la textura y sobre la cual se va a trabajar
	SDL_Texture* textura = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ventana->w, ventana->h);

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
		filledCircleColor(renderer, radio, radio, radio, color);
		filledCircleColor(renderer, radio, radio + radio / 2, radio / 4, color + 0xFF00);
		delete pos;
	}
	//Si no es circulo
	else {
		short vx[cantVertices];
		short vy[cantVertices];
		Pos* centroFigura = getPosCentro(vertices);
		Pos* centroVentana = new Pos(ventana->w / 2, ventana->w / 2);
		for (int i = 0; i < cantVertices; i++) {
			vx[i] = vertices->at(i)->getX() - centroFigura->getX() + centroVentana->getX();
			vy[i] = vertices->at(i)->getY() - centroFigura->getY() + centroVentana->getY();
		}
		filledPolygonColor(renderer, vx, vy, cantVertices, color);
		delete centroFigura;
		delete centroVentana;
	}

	//Se modifica el target del renderer para que ahora apunte a la ventana (valor por defecto)
	SDL_SetRenderTarget(renderer, NULL);

	SDL_Texture* texturaRotada = this->rotar(textura, objeto->getRotacion());
	SDL_DestroyTexture(textura);

	liberarVertices(*vertices);
	delete vertices;

	return texturaRotada;
}

/*
 * \return 	SDL_Rect para obtener la posicion y el tamaño de la textura obtenida por el
 * 			método getVista(). Se devuelve un objeto de tipo "const" ya que no debe (ni se puede) modificar
 * 			su contenido, pero si puede consultarse.
 */

const SDL_Rect* ObjetoMapaVista::getVentana() {
	Pos* p = objeto->getPos()->ySimetrico();
	ventana->x = p->getX() - ventana->w / 2;
	ventana->y = p->getY() - ventana->h / 2;
	delete p;
	return ventana;
}

ObjetoMapaVista::~ObjetoMapaVista() {}

/**
 * \param	vPos 	vector de posiciones.
 *
 * \return 	Posición (Xmin, Ymin), siendo Xmin el mínimo 'x'
 * 			dentro de entre todas posiciones que integran al vector vPos
 * 			y siendo Ymin el mínimo 'y' dentro de entre todas las posiciones
 * 			que integran al vector vPos.
 * 			Observar que Xmin, Ymin no tienen que pertenecer al mismo elemento
 * 			dentro del vector vPos.
 *
 * \obs		Se llama getPosInzSup ya que en SDL el punto (0,0) u origen de
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

/**
 * \param	vPos 	vector de posiciones.
 *
 * \return 	Posición (Xmax, Ymax), siendo Xmax el maximo 'x'
 * 			dentro de entre todas posiciones que integran al vector vPos
 * 			y siendo Ymax el maximo 'y' dentro de entre todas las posiciones
 * 			que integran al vector vPos.
 * 			Observar que Xmax, Ymax no tienen que pertenecer al mismo elemento
 * 			dentro del vector vPos.
 *
 * \obs		Se llama getPosDerInf ya que en SDL el punto (0,0) u origen de
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

/**
 * \brief	Calcula el rectángulo de mínima área que puede contener al contorno generado por
 * 				los vertices pasados por parametro \vPos y luego calcula la posición que ocupa
 * 				el centro de dicho rectágulo
 *
 * \param 	vPos 	vector de posiciones (contorno).
 *
 * \return	Pos		centro del contorno.
 */
Pos* ObjetoMapaVista::getPosCentro(std::vector<Pos*>* vPos){
	Pos* pIzqSup = getPosIzqSup(vPos);
	Pos* pDerInf = getPosDerInf(vPos);
	int x = ( pDerInf->getX() + pIzqSup->getX() ) /2;
	int y = ( pDerInf->getY() + pIzqSup->getY() ) /2;
	return new Pos(x,y);
}

/**
 * \brief	Se genera una nueva textura de igual tamaño que la recibida \t, pero rotada una
 * 				cantidad de grados determinados por \grados, con respecto a su centro.
 *
 * \param	\t			Textura a rotar. No se modifica esta textura.
 * \param	\grados		Cantidad de gados que se debe rotar la textura.
 *
 * \obs		\t no se modifica ni se destruye. Esto debe hacerse de forma externa.
 */
SDL_Texture* ObjetoMapaVista::rotar(SDL_Texture* t, double grados){
	//Se crea una textura donde se guardara la imagen rotada
	SDL_Texture* texturaRotada = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ventana->w, ventana->h);

	//Se pone a la textura como target del render
	SDL_SetRenderTarget(renderer, texturaRotada);

	//Se pinta con pixeles transparentes a la textura
	SDL_SetTextureBlendMode(texturaRotada, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Se rota la imagen
	SDL_RenderCopyEx(renderer, t, NULL, NULL, -grados, NULL, SDL_FLIP_NONE);

	//Se modifica el target del renderer para que ahora apunte a la ventana (valor por defecto)
	SDL_SetRenderTarget(renderer, NULL);

	return texturaRotada;
}
