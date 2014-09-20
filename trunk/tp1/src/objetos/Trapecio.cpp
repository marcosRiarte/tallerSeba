#include "Trapecio.h"

Trapecio::Trapecio(Pos posicion, int base, int altura, int alfa, int beta,int rotacion,std::string color,int masa,bool estatico){
	this->base = base;
	this->altura = altura;
	this->alfa = alfa;
	this->beta = beta;
	this->initialice(estatico, color, posicion, rotacion, masa);
}

std::vector<Pos*>* Trapecio::getContorno() {
	return nullptr;
}

float Trapecio::getArea(){
	double h = this->altura;
	double  b1 = h/tan(this->alfa);
	double b3 = h/tan(this->beta);
	double b2 = (this->base - (b1 + b3));
	return ((b1*h/2) + (b2*h) + (b3*h/2));
}

Trapecio::~Trapecio() {
	// TODO Auto-generated destructor stub
}

