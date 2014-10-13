#include "Poligono.h"
#include <math.h>

Poligono::Poligono(Pos posicion, int lados, int escala, int rotacion, std::string color, int masa, bool estatico) {
	this->lados = lados;
	this->escala = escala;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

void Poligono::crearContorno() {
	const double PI = 4.0 * atan(1.0);
	for (int i = 0; i < lados; i++) {
		int x = escala * cos(2 * PI * i / lados);
		int y = escala * sin(2 * PI * i / lados);
		Pos posicion = Pos(x, y);
		vertices.push_back(posicion);
	}
}

Poligono::~Poligono() {
	this->lados = 0;
	this->escala = 0;
}

float Poligono::getArea() {
	const double PI = 4.0 * atan(1.0);
	int n = this->lados;
	float alfa = 2 * PI / n;
	int r = this->escala;
	return (n * r * r * sin(alfa * PI / 180)) / 2;
}

