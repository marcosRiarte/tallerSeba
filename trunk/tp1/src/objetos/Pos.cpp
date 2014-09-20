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

float Pos::getNorma(){
	return sqrt(x*x + y*y);
}

Pos::~Pos() {
	// TODO Auto-generated destructor stub
}

