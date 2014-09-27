#include "ObjetoMapa.h"
#include "../Constantes.h"
#include <math.h>
#include <exception>


void ObjetoMapa::initialice(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa) {
		this->estatico = esEstatico;
		this->color = color;
		this->pos = new Pos(pos_cm);
		this->rot = rotacion;
		this->masa = masa;
}

bool ObjetoMapa::esCirculo() {
	return false;
}

bool ObjetoMapa::esEstatico() {
	return this->estatico;
}

float ObjetoMapa::getDensidad() {
	return this->masa / this->getArea();
}

long ObjetoMapa::getColor(){
	long colorInt = 0;
	for( unsigned i = 0; i < color.length() - 1 ; i++ ){
		switch( color[ color.length() - 1 - i ] ){
		case('0'): break;
		case('1'): colorInt = colorInt + pow(16, i); break;
		case('2'): colorInt = colorInt + pow(16, i) * 2; break;
		case('3'): colorInt = colorInt + pow(16, i) * 3; break;
		case('4'): colorInt = colorInt + pow(16, i) * 4; break;
		case('5'): colorInt = colorInt + pow(16, i) * 5; break;
		case('6'): colorInt = colorInt + pow(16, i) * 6; break;
		case('7'): colorInt = colorInt + pow(16, i) * 7; break;
		case('8'): colorInt = colorInt + pow(16, i) * 8; break;
		case('9'): colorInt = colorInt + pow(16, i) * 9; break;
		case('A'):case('a'): colorInt = colorInt + pow(16, i) * 10; break;
		case('B'):case('b'): colorInt = colorInt + pow(16, i) * 11; break;
		case('C'):case('c'): colorInt = colorInt + pow(16, i) * 12; break;
		case('D'):case('d'): colorInt = colorInt + pow(16, i) * 13; break;
		case('E'):case('e'): colorInt = colorInt + pow(16, i) * 14; break;
		case('F'):case('f'): colorInt = colorInt + pow(16, i) * 15; break;
		default:
			throw;
		}
	}
	return colorInt;
}

void ObjetoMapa::setColor(std::string c) {
	this->color = c;
}

Pos* ObjetoMapa::getPos() {
	return pos;
}

void ObjetoMapa::setPos(Pos* posicion) {
	pos = posicion;
}

int ObjetoMapa::getRotacion() {
	return rot;
}

void ObjetoMapa::setRotacion(float rotacion) {
	rot = rotacion;
}

int ObjetoMapa::getMasa() {
	return masa;
}

// getter y setter de link a mundo
void ObjetoMapa::setLinkAMundo(b2Body* link) {
	linkAMundo = link;
}

b2Body* ObjetoMapa::getLinkAMundo() {
	return linkAMundo;
}

