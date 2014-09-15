#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../objetos/Pos.h"

class Personaje {
private:
	Pos* pos;

public:
	Personaje(Pos* posicion);

	// getter y setter de la posicion
	void setPosicion(Pos* posicion);
	Pos getPosicion();

	// devuelve verdadero si esta en esa posicion
	bool estaEnPos(Pos* posicion);

	virtual ~Personaje();
};

#endif /* PERSONAJE_H_ */
