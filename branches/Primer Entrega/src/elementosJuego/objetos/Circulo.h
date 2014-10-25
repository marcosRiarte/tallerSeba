#ifndef CIRCULO_H_
#define CIRCULO_H_
#include "ObjetoMapa.h"

class Circulo: public ObjetoMapa {
private:
	int diametro;
	void crearContorno();
	void calcularArea();
public:
	Circulo(Pos posicion, int diametro, int rotacion, std::string color, int masa, bool estatico);
	bool esCirculo();
	virtual ~Circulo();
};

#endif /* CIRCULO_H_ */
