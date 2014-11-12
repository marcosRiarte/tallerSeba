#ifndef RECTANGULO_H_
#define RECTANGULO_H_

#include "ObjetoMapa.h"

class Rectangulo: public ObjetoMapa {
private:
	int alto;
	int ancho;
	void crearContorno();
	void calcularArea();
public:
	Rectangulo(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa, int alto, int ancho);
	virtual ~Rectangulo();
};

#endif /* RECTANGULO_H_ */
