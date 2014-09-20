#include "Poligono.h"
#include <math.h>

Poligono::Poligono(Pos posicion, int lados, int escala, int rotacion,std::string color,int masa,bool estatico) {
	this->lados = lados;
	this->escala = escala;
	this->initialice(estatico, color, posicion, rotacion, masa);
	this->vertices = std::vector<Pos*>();
}

std::vector<Pos*>* Poligono::getContorno() {
	const double PI = 4.0*atan(1.0);
	for (int i = 0; i < lados; i++) {
 	int x = (((this->pos->getX()) + escala) * cos((2 * PI * i *PI/180)/ lados));
 	int y = (y + escala * sin((2 * PI * i *PI/180 )/ lados));
 	Pos* posicion = new Pos(x,y);
	  vertices.push_back(posicion);
	}
	return &vertices;
}

Poligono::~Poligono() {
	// TODO Auto-generated destructor stub
}

