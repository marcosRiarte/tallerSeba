#ifndef TRAPECIO_H_
#define TRAPECIO_H_

#include "ObjetoMapa.h"

class Trapecio: public ObjetoMapa {
private:
	int base;
	int altura;
	int alfa;
	int beta;
public:
	Trapecio(Pos posicion, int base, int altura, int alfa, int beta,int rotacion,std::string color,int masa,bool estatico);
	std::vector<Pos*>* getContorno();
	virtual ~Trapecio();
};

#endif /* TRAPECIO_H_ */
