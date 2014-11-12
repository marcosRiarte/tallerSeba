#ifndef ELEMENTOSJUEGO_H_
#define ELEMENTOSJUEGO_H_

#include "Pos.h"

/*
 * Clase Abrstracta (no se pueden crear instancias de la misma) que sirve de base para
 * 	los demas objetos que hereden de ella. Es una interfaz
 * 	Objetos que heredan: ObjetoMapa,Personaje.
 */
class ElementosJuego {
protected:
	Pos pos;
	unsigned int ID;

public:
	/*
	 * Devuelvey setea el ID del objeto. Que es lo mismo que su DNI
	 */
	unsigned int getID();
	void setID(unsigned int ID);

	/*
	 * Getter y setter para la posicion
	 */
	Pos getPos();
	void setPos(Pos posicion);

	virtual ~ElementosJuego();
};

#endif /* ELEMENTOSJUEGO_H_ */
