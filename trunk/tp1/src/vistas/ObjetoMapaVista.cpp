#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include <string>
#include <math.h>
#include "ObjetoMapaVista.h"
#include "../Constantes.h"


ObjetoMapaVista::ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa* o) {
	objeto = o;
	this->setRenderer(r);
	ventana = SDL_Rect();

	//Obtengo los vértices, transformando cada vertice en su simétrico respecto del eje Y
	std::vector<Pos> vertices = objeto->getContorno();
	for (unsigned i = 0; i < vertices.size(); i++) {
		vertices.at(i) = vertices.at(i).ySimetrico();
	}

	int diametro;

	//Se calcula la superficie que puede llegar a ocupar dicho objeto, teniendo en cuenta
	//	las posibles rotaciones.
	if (objeto->esCirculo()) {
		Pos pos = objeto->getPos().ySimetrico();
		diametro = 2 * vertices.at(0).getNorma()+1;
	}else {
		Pos pIzqSup = getPosIzqSup(vertices);
		Pos pDerInf = getPosDerInf(vertices);
		diametro = pIzqSup.getDistancia(pDerInf);
	}
	ventana.w = diametro;
	ventana.h = diametro;

	//Se crea la textura y sobre la cual se va a trabajar
	textura = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, ventana.w, ventana.h);

}


/**
 * \return	Textura, cuyo tamaño y posición se puede adquirir por medio del método
 * 			getVentana(). Observar que la textura debe ser liberada por el objeto que la recibe, ya
 * 			que se genera una textura por cada vez que se llama a este método.
 */
SDL_Texture* ObjetoMapaVista::getVista() {

	long color = ( objeto->getColor() ) + 0xFF000000;

	//Obtengo los vértices, transformando cada vertice en su simétrico respecto del eje Y
	std::vector<Pos> vertices = objeto->getContorno();
	for (unsigned i = 0; i < vertices.size(); i++) {
		vertices.at(i) = vertices.at(i).ySimetrico();
	}

	int cantVertices = vertices.size();

	//Se pone a la textura como target del render
	SDL_SetRenderTarget(renderer, textura);

	//Se pinta con pixeles transparentes a la textura
	SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Se dibuja la figura segun su tipo (taxonomía: circulo, no-circulo)
	//Si es circulo
	if (objeto->esCirculo()) {
		Pos p = vertices.at(0);
		int radio = p.getNorma();
		double angulo = atan2(p.getY(), p.getX());
		int x = (radio / 2) * cos(angulo - objeto->getRotacion() * M_PI / 180) + radio+0.5;
		int y = (radio / 2) * sin(angulo - objeto->getRotacion() * M_PI / 180) + radio+0.5;
		filledCircleColor(renderer, radio, radio, radio, color);
		filledCircleColor(renderer, x, y, radio / 4, color + 0xF0F0F0);
	}
	//Si no es circulo
	else {
		short vx[cantVertices];
		short vy[cantVertices];
		Pos centroVentana = Pos(ventana.w / 2, ventana.w / 2);
		for (int i = 0; i < cantVertices; i++) {
			Pos p = vertices.at(i);
			double angulo = atan2(p.getY(), p.getX());
			vx[i] = p.getNorma() * cos(angulo - objeto->getRotacion() * M_PI / 180) + centroVentana.getX()+0.5;
			vy[i] = p.getNorma() * sin(angulo - objeto->getRotacion() * M_PI / 180) + centroVentana.getY()+0.5;
		}
		filledPolygonColor(renderer, vx, vy, cantVertices, color);
	}

	//Se modifica el target del renderer para que ahora apunte a la ventana (valor por defecto)
	SDL_SetRenderTarget(renderer, NULL);

	return textura;
}

/*
 * \return 	SDL_Rect para obtener la posicion y el tamaño de la textura obtenida por el
 * 			método getVista(). Se devuelve un objeto de tipo "const" ya que no debe (ni se puede) modificar
 * 			su contenido, pero si puede consultarse.
 */

const SDL_Rect ObjetoMapaVista::getVentana() {
	Pos p = objeto->getPos().ySimetrico();
	ventana.x = p.getX() - ventana.w / 2;
	ventana.y = p.getY() - ventana.h / 2;
	return ventana;
}

ObjetoMapaVista::~ObjetoMapaVista() {
	SDL_DestroyTexture(textura);
}

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
Pos ObjetoMapaVista::getPosIzqSup(std::vector<Pos> vPos) {
	Pos p = vPos.at(0);
	int Xmin = p.getX();
	int Ymin = p.getY();
	for (unsigned i = 1; i < vPos.size(); i++) {
		p = vPos.at(i);
		if (p.getX() < Xmin)
			Xmin = p.getX();
		if (p.getY() < Ymin)
			Ymin = p.getY();
	}
	return Pos(Xmin, Ymin);
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
Pos ObjetoMapaVista::getPosDerInf(std::vector<Pos> vPos) {
	Pos p = vPos.at(0);
	int Xmax = p.getX();
	int Ymax = p.getY();
	for (unsigned i = 1; i < vPos.size(); i++) {
		p = vPos.at(i);
		if (p.getX() > Xmax)
			Xmax = p.getX();
		if (p.getY() > Ymax)
			Ymax = p.getY();
	}
	return Pos(Xmax, Ymax);
}
