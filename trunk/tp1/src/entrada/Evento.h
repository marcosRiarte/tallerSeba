/*
 * Representa un evento de entrada
 */

#ifndef EVENTO_H_
#define EVENTO_H_

#include <iostream>

using namespace std;

class Evento {
private:
	// No val�a la pena hacer mas clases, ac� ponemos los valores posibles:
	// arriba, derecha, izquierda, nada.
	string teclaIngresada;
public:
	Evento();

	// geter y seter para la tecla
	void setTecla(string tecla);
	string getTecla();

	virtual ~Evento();
};


#endif /* EVENTO_H_ */
