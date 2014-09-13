/*
 * Representa un evento de entrada
 */

#ifndef EVENTO_H_
#define EVENTO_H_

#include <vector>
#include <string>

using namespace std;

class Evento {
private:
	// No vali la pensa hacer mas clases, aca ponemos los valores posibles:
	// arriba, derecha, izquierda.
	string teclaIngresada;
public:
	//void Evento();

	// geter y seter para la tecla
	void setTecla(string tecla);
	void getTecla(string tecla);

	virtual ~Evento();
};


#endif /* EVENTO_H_ */
