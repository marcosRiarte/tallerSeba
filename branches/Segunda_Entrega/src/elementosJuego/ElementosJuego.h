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
	float area;
	Pos pos;
	b2Body* linkAMundo;
	float friccion;
	std::vector<Pos> vertices = std::vector<Pos>();

	virtual void crearContorno() = 0;
	virtual void calcularArea() = 0;

	static int cantidadDeInstancias;
	const int ID = cantidadDeInstancias;

	ElementosJuego(){
		this->cantidadDeInstancias++;
	}

public:
	/*
	 * Devuelve el ID del objeto. Que es lo mismo que su DNI
	 */
	int getID();

	/*
	 * Devuelve verdadero si el objeto no se puede mover
	 */
	virtual bool esEstatico() = 0;

	/*
	 * Devuelve verdadero si el objeto es un circulo
	 */
	virtual bool esCirculo() = 0;

	/*
	 * Devuelve la densidad del elemento
	 */
	float getDensidad();

	/*
	 * Devuelve la friccion del elemento
	 */
	float getFriccion();

	/*
	 * Devuelve los puntos del contorno del elemento
	 */
	std::vector<Pos> getContorno();

	/*
	 * Devuelve el area del elemento
	 */
	float getArea();

	/*
	 * Getter y setter para la posicion
	 */
	Pos getPos();
	void setPos(Pos posicion);

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
