#include "Poligono.h"
#include <math.h>

Poligono::Poligono(Pos posicion, int lados, int escala, int rotacion,std::string color,int masa,bool estatico) {
	this->lados = lados;
	this->escala = escala;
	this->initialice(estatico, color, posicion, rotacion, masa);
	}

std::vector<Pos*>* Poligono::getContorno() {

	std::vector<Pos*>* vertices = new std::vector<Pos*>();
	const double PI = 4.0*atan(1.0);
	for (int i = 0; i < lados; i++) {
 	int x = (this->pos->getX() + (escala * cos((2 * PI * i / lados))));
 	int y = (this->pos->getY() + (escala * sin((2 * PI * i / lados))));
 	Pos* posicion = new Pos(x,y);
	  vertices->push_back(posicion);
	}
	return vertices;
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

