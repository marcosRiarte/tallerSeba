#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../objetos/Pos.h"

class Personaje {
private:
	Pos* pos;
	float rot;

public:
	Personaje(Pos* posicion,float rotacion);

	// getter y setter de la posicion
	void setPosicion(Pos* posicion);
	Pos* getPosicion();

	float getRotacion();

	// devuelve verdadero si esta en esa posicion
	bool estaEnPos(Pos* posicion);

	virtual ~Personaje();
};

#endif /* PERSONAJE_H_ */
