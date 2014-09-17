/*
 * Circulo.h
 *
 *  Created on: 14/9/2014
 *      Author: Seba
 */

#ifndef CIRCULO_H_
#define CIRCULO_H_
#include "ObjetoMapa.h"

class Circulo : public ObjetoMapa {
private:
	int diametro;
public:
	Circulo(Pos* posicion, int diametro, int rotacion, std::string color, int masa, bool estatico);
	std::vector<Pos>* getContorno();
	virtual ~Circulo();
};

#endif /* CIRCULO_H_ */
