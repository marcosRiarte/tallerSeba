#include "ObjetoMapa.h"
#include <math.h>

/**
 * \brief	Toma un string, con caracteres representables por un número hexadecimal [1-9 A-F]
 * 			y devuelve un valor entero que lo representa.
 * 			Por ejemplo: stringToHexa("AA123F") retorna 0xAA123F
 *
 * \param	s	String del tipo 0xAAVVRR.
 *
 * \return	valor entero que representa s.
 */
long stringToHexa(std::string s){
	long longValue = 0;
    for( unsigned i = 0; i < s.length(); i++ ){
    	switch( s[ s.length() - 1 - i ] ){
        	case('0'): break;
        	case('1'): longValue = longValue + pow(16, i); break;
            case('2'): longValue = longValue + pow(16, i) * 2; break;
            case('3'): longValue = longValue + pow(16, i) * 3; break;
            case('4'): longValue = longValue + pow(16, i) * 4; break;
            case('5'): longValue = longValue + pow(16, i) * 5; break;
            case('6'): longValue = longValue + pow(16, i) * 6; break;
            case('7'): longValue = longValue + pow(16, i) * 7; break;
            case('8'): longValue = longValue + pow(16, i) * 8; break;
            case('9'): longValue = longValue + pow(16, i) * 9; break;
            case('A'):case('a'): longValue = longValue + pow(16, i) * 10; break;
            case('B'):case('b'): longValue = longValue + pow(16, i) * 11; break;
            case('C'):case('c'): longValue = longValue + pow(16, i) * 12; break;
            case('D'):case('d'): longValue = longValue + pow(16, i) * 13; break;
            case('E'):case('e'): longValue = longValue + pow(16, i) * 14; break;
            case('F'):case('f'): longValue = longValue + pow(16, i) * 15; break;
            default:
            	throw;
    	}
    }
    return longValue;
}

ObjetoMapa::ObjetoMapa(){
	estatico = true;
	color = 0;
	pos = Pos();
	rot = 0;
	vertices = std::vector<Pos>();
}

ObjetoMapa::ObjetoMapa(bool esEstatico, long lColor, Pos pos_cm, int rotacion, std::vector<Pos> contorno) {
	estatico = esEstatico;
	color = lColor;
	pos = new Pos(pos_cm);
	rot = rotacion;
	vertices = contorno;
}

/*
 * Devuelve verdadero si el objeto no se puede mover
 */
bool ObjetoMapa::esEstatico() {
	return this->estatico;
}

/*
 * Devuelve verdadero si el objeto es un circulo
 */
bool ObjetoMapa::esCirculo() {
	return false;
}

/*
 * Getter y setter para el color del objeto
 */
long ObjetoMapa::getColor() {
	return color;
}

void ObjetoMapa::setColor(std::string color) {
	this->color = stringToHexa(color.substr(1, color.npos));
}

/*
 * Devuelve un vector de Posiciones que define el contorno de la figura
 */
std::vector<Pos> ObjetoMapa::getContorno() {
	return vertices;
}

/*
 * Getter y setter para el angulo de rotacion
 */
float ObjetoMapa::getRotacion() {
	return rot;
}

void ObjetoMapa::setRotacion(float rotacion) {
	rot = rotacion;
}

ObjetoMapa::~ObjetoMapa() {
}
