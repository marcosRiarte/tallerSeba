/*
 * Poligono.h
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "ObjetoMapa.h"


class Poligono : public ObjetoMapa {
private:
	int lados;
	int escala;
public:
	Poligono(Pos posicion, int lados, int escala, int rotacion,std::string color,int masa,bool estatico);
	std::vector<Pos>* getContorno();
	virtual ~Poligono();
};

#endif /* POLIGONO_H_ */
