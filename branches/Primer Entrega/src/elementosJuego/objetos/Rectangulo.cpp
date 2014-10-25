#include "Rectangulo.h"

Rectangulo::Rectangulo(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa, int alto, int ancho) {
	this->alto = alto;
	this->ancho = ancho;
	this->initialice(esEstatico, color, pos_cm, rotacion, masa);
}

void Rectangulo::crearContorno() {
	int x1 = -ancho / 2;
	int y1 = -alto / 2;
	int x2 = x1 + ancho;
	int y2 = y1;
	int x3 = x2;
	int y3 = y2 + alto;
	int x4 = x1;
	int y4 = y3;

	Pos posicion1 = Pos(x1, y1);
	Pos posicion2 = Pos(x2, y2);
	Pos posicion3 = Pos(x3, y3);
	Pos posicion4 = Pos(x4, y4);
	vertices.push_back(posicion1);
	vertices.push_back(posicion2);
	vertices.push_back(posicion3);
	vertices.push_back(posicion4);
}

void Rectangulo::calcularArea() {
	area = (this->alto * this->ancho);
}

Rectangulo::~Rectangulo() {
}
