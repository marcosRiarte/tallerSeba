#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "ObjetoMapa.h"

class Poligono: public ObjetoMapa {
private:
	int lados;
	int escala;
	void crearContorno();
	void calcularArea();
public:
	Poligono(Pos posicion, int lados, int escala, int rotacion, std::string color, int masa, bool estatico);
	virtual ~Poligono();
};

#endif /* POLIGONO_H_ */
