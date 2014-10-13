#ifndef CIRCULO_H_
#define CIRCULO_H_
#include "ObjetoMapa.h"

class Circulo: public ObjetoMapa {
private:
	int diametro;
public:
	Circulo(Pos posicion, int diametro, int rotacion, std::string color, int masa, bool estatico);
	bool esCirculo();
	std::vector<Pos> getContorno();
	float getArea();
	virtual ~Circulo();
};

#endif /* CIRCULO_H_ */
