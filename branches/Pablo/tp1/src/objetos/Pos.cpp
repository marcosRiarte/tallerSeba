#include "Pos.h"

Pos::Pos(int x, int y) {
	this->x = x;
	this->y = y;
}

int Pos::getX(){
	return x;
}

int Pos::getY(){
	return y;
}

Pos::Pos(const Pos &p) {
	x = p.x;
	y = p.y;
}

bool Pos::operator == (const Pos& p){
	if ( (x == p.x) && (y == p.y) )
		return true;
	return false;
}

Pos& Pos::operator = (const Pos& p){
	if (this != p){
		x = p.x;
		y = p.y;
	}
	return this;
}

Pos::~Pos() {
	// TODO Auto-generated destructor stub
}

