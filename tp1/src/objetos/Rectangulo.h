#ifndef RECTANGULO_H_
#define RECTANGULO_H_

#include "ObjetoMapa.h"

class Rectangulo: ObjetoMapa {
private:
	int alto;
	int ancho;
public:
	Rectangulo(bool esEstatico, Color color, Pos pos_cm, int rotacion, float masa, int alto, int ancho);
	std::vector<Pos>* getContorno();
	virtual ~Rectangulo();
};

#endif /* RECTANGULO_H_ */
