#ifndef ELEMENTOSJUEGO_H_
#define ELEMENTOSJUEGO_H_

#include <vector>
#include <string>
#include "Pos.h"
#include <Box2D/Box2D.h>

/*
 * Clase Abrstracta (no se pueden crear instancias de la misma) que sirve de base para
 * 	los demas objetos que hereden de ella. Es una interfaz
 * 	Objetos que heredan: ObjetoMapa,Personaje.
 */
class ElementosJuego {
protected:
	float masa;
	float rot;
	Pos* pos;
	b2Body* linkAMundo;

public:
	/*
	 * Devuelve la densidad del elemento
	 */
	float getDensidad();

	/*
	 * Devuelve los puntos del contorno del elemento
	 */
	virtual std::vector<Pos*>* getContorno() = 0;

	/*
	 * Devuelve el area del elemento
	 */
	virtual float getArea() = 0;

	/*
	 * Getter y setter para la posicion
	 */
	Pos* getPos();
	void setPos(Pos* posicion);

	/*
	 * Getter y setter para el angulo de rotacion
	 */
	float getRotacion();
	void setRotacion(float rotacion);

	/*
	 * Getter y setter para el link al mundo
	 */
	void setLinkAMundo(b2Body* link);
	b2Body* getLinkAMundo();

	virtual ~ElementosJuego();
};

#endif /* ELEMENTOSJUEGO_H_ */
