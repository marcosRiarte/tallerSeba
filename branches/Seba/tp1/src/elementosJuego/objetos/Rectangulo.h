#ifndef RECTANGULO_H_
#define RECTANGULO_H_

#include "ObjetoMapa.h"

class Rectangulo: public ObjetoMapa {
private:
	int alto;
	int ancho;
public:
	Rectangulo(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa, int alto, int ancho);
	std::vector<Pos>* getContorno();
	float getArea();
	virtual ~Rectangulo();
};

#endif /* RECTANGULO_H_ */
