/*
 * Paralelogramo.cpp
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#include "Paralelogramo.h"
#include <math.h>

Paralelogramo::Paralelogramo(Pos posicion, int base, int ladoaltura, int alfa, int rotacion,std::string color,int masa,bool estatico) {
	this->base = base;
	this->altura = ladoaltura;
	this->alfa = alfa;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

std::vector<Pos*>* Paralelogramo::getContorno() {
	std::vector<Pos*> vertices;
	if ((this->alfa)<90){
	int x1 = ((this->pos->getX())-(((this->base)+((this->altura)*cos(alfa)))/2));
	int y1 = ((this->pos->getY()))-((this->altura)*sin(alfa)/2);
	int x2 = x1+base;
	int y2 = y1;
	int x3 = x2 + ((this->altura)*cos(alfa));
	int y3 = y2 + ((this->altura)*sin(alfa));
	int x4 = x3 - (this->base);
	int y4 = y3;
	Pos* posicion1 = new Pos(x1,y1);
	Pos* posicion2 = new Pos(x2,y2);
	Pos* posicion3 = new Pos(x3,y3);
	Pos* posicion4 = new Pos(x4,y4);
	vertices.push_back(posicion1);
	vertices.push_back(posicion2);
	vertices.push_back(posicion3);
	vertices.push_back(posicion4);
	}
	else{
		int beta = 180 - alfa ;
		int x1 = ((this->pos->getX())-(((this->base)+((this->altura)*cos(beta)))/2));
		int y1 = ((this->pos->getY()))-((this->altura)*sin(beta)/2);
		int x2 = x1+base;
		int y2 = y1;
		int x3 = x2 - ((this->altura)*cos(beta));
		int y3 = y2 + ((this->altura)*sin(beta));
		int x4 = x3 - (this->base);
		int y4 = y3;
		Pos* posicion1 = new Pos(x1,y1);
		Pos* posicion2 = new Pos(x2,y2);
		Pos* posicion3 = new Pos(x3,y3);
		Pos* posicion4 = new Pos(x4,y4);
		vertices.push_back(posicion1);
		vertices.push_back(posicion2);
		vertices.push_back(posicion3);
		vertices.push_back(posicion4);
	}
	return &vertices;
}

Paralelogramo::~Paralelogramo() {
	// TODO Auto-generated destructor stub
}

