#ifndef PARALELOGRAMO_H_
#define PARALELOGRAMO_H_

#include "ObjetoMapa.h"

class Paralelogramo: public ObjetoMapa {
private:
	int base;
	int altura;
	int alfa;
public:
	Paralelogramo(Pos posicion, int base, int altura, int alfa, int rotacion,std::string color,int masa,bool estatico);
	std::vector<Pos>* getContorno();
	float getArea();
	virtual ~Paralelogramo();
};

#endif /* PARALELOGRAMO_H_ */
