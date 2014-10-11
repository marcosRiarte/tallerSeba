#include "Pos.h"
#include <Math.h>

Pos::Pos(int x, int y) {
	this->x = x;
	this->y= y;
}

int Pos::getX(){
	return this->x;
}

int Pos::getY(){
	return this->y;
}

Pos::Pos(const Pos* p) {
	x = p->x;
	y = p->y;
}

bool Pos::esIgual(Pos* posicion){
	if ( (posicion->x == x) && (posicion->y == y) )
		return true;
	else
		return false;
}
/*
 * @return Distancia al origen de coordenadas (0,0).
 */
float Pos::getNorma(){
	return sqrt(x*x + y*y);
}

/*
 * @param p posición desde la cual se mide la distancia.
 * @return Distancia a p.
 */
float Pos::getDistancia(Pos* p){
	int x = this->x - p->x;
	int y = this->y - p->y;
	return sqrt(x*x + y*y);
}

/*
 * @return posición simétrica a this respecto del eje Y.
 */
Pos* Pos::ySimetrico(){
	return new Pos(x, -y);
}

Pos::~Pos() {
}

