/*
 * Pos.cpp
 *
 *  Created on: 9/9/2014
 *      Author: pablo_000
 */

#include "Pos.h"

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
	return true;
}

Pos::~Pos() {
	// TODO Auto-generated destructor stub
}

