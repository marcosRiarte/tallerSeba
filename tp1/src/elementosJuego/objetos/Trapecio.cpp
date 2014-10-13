#include "Trapecio.h"

Trapecio::Trapecio(Pos posicion, int base, int altura, int alfa, int beta, int rotacion, std::string color, int masa, bool estatico) {
	this->base = base;
	this->altura = altura;
	this->alfa = alfa;
	this->beta = beta;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

void Trapecio::crearContorno() {
	const double PI = 4.0 * atan(1.0);

	int x1 = -base / 2;
	int y1 = -altura / 2;
	int x2 = x1 + base;
	int y2 = y1;
	int x3 = x2 - ((this->altura) / tan(beta * PI / 180));
	int y3 = y1 + altura;
	int x4 = x1 + ((this->altura) / tan(alfa * PI / 180));
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

float Trapecio::getArea() {
	const double PI = 4.0 * atan(1.0);
	double h = this->altura;
	double b1 = h / tan(this->alfa * PI / 180);
	double b3 = h / tan(this->beta * PI / 180);
	double b2 = (this->base - (b1 + b3));
	return ((b1 * h / 2) + (b2 * h) + (b3 * h / 2));
}

Trapecio::~Trapecio() {
	this->base = 0;
	this->altura = 0;
	this->alfa = 0;
	this->beta = 0;
}
