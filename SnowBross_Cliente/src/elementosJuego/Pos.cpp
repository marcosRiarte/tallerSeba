#include "Pos.h"
#include <Math.h>

Pos::Pos(int x, int y) {
	this->x = x;
	this->y = y;
}

Pos::Pos() {
	x = 0;
	y = 0;
}

int Pos::getX() {
	return this->x;
}

int Pos::getY() {
	return this->y;
}

Pos::Pos(const Pos* p) {
	x = p->x;
	y = p->y;
}

/*
 * @return Distancia al origen de coordenadas (0,0).
 */
float Pos::getNorma() {
	return sqrt(x * x + y * y);
}

/*
 * @param p posición desde la cual se mide la distancia.
 * @return Distancia a p.
 */
float Pos::getDistancia(Pos p) {
	int x = this->x - p.x;
	int y = this->y - p.y;
	return sqrt(x * x + y * y);
}

Pos::~Pos() {
}

