/* Contiene las características de la configuración de la pantalla
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

// Devuelve un vector que contiene [alto,ancho]
vector<int> Pantalla::getDimensionesPx() {
	vector<int> dimensiones(2);
	dimensiones[0] = altoPx;
	dimensiones[1] = anchoPx;
	return dimensiones;
}

// Devuelve un vector que contiene [altoPx,anchoPx]
vector<int> Pantalla::getDimensiones() {
	vector<int> dimensiones(2);
	dimensiones[0] = alto;
	dimensiones[1] = ancho;
	return dimensiones;
}

// Devuelve la dirección donde se encuentra la imagen de fondo
string Pantalla::getFondo() {
	return dirImg;
}

Pantalla::~Pantalla() {}

