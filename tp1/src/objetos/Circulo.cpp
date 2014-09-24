#include "Circulo.h"

Circulo::Circulo(Pos posicion, int diametro,int rotacion,std::string color,int masa,bool estatico){
	this->circulo = true;
	this->diametro = diametro;
	this->initialice(estatico, color, posicion, rotacion, masa);

}
/*
 * @return Devuelve un vector con una sola posición (p). De esta manera, se puede calcular
 * 			su radio, haciendo | getPos() - p |
 */
std::vector<Pos*>* Circulo::getContorno() {

	std::vector<Pos*>* vertices = new std::vector<Pos*>();
	int x = pos->getX()+(diametro/2);
	int y = pos->getY();
	Pos* posicion = new Pos(x,y);
	vertices->push_back(posicion);
	return vertices;
}

float Circulo::getArea(){
	const double PI = 4.0*atan(1.0);
	return PI*(diametro*diametro)/4;
}

Circulo::~Circulo() {
	// TODO Auto-generated destructor stub
}

