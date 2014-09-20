#include "Circulo.h"

Circulo::Circulo(Pos posicion, int diametro,int rotacion,std::string color,int masa,bool estatico){
	this->diametro = diametro;
	this->initialice(estatico, color, posicion, rotacion, masa);

}
/*
 * @return Devuelve un vector con una sola posición (p). De esta manera, se puede calcular
 * 			su radio, haciendo | getPos() - p |
 */
std::vector<Pos*>* Circulo::getContorno() {
	return nullptr;
}


Circulo::~Circulo() {
	// TODO Auto-generated destructor stub
}

