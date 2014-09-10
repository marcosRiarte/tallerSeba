/*
 * Pantalla.cpp
 *
 *  Created on: 6/9/2014
 *      Author: pablo_000
 */

#include "Pantalla.h"

Pantalla::Pantalla(int altoPx, int anchoPx, int alto, int ancho,
		string dirImg) {
	this->altoPx = altoPx;
	this->anchoPx = anchoPx;
	this->alto = alto;
	this->ancho = ancho;
	this->dirImg = dirImg;
}

vector<int> Pantalla::getDimensionesPx() {
	vector<int> dimensiones(2);
	dimensiones[0] = altoPx;
	dimensiones[1] = anchoPx;
	return dimensiones;
}

vector<int> Pantalla::getDimensiones() {
	vector<int> dimensiones(2);
	dimensiones[0] = alto;
	dimensiones[1] = ancho;
	return dimensiones;
}

string Pantalla::getFondo() {
	return dirImg;
}

Pantalla::~Pantalla() {}

