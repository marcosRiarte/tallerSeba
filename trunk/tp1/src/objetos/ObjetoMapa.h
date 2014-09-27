#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include <vector>
#include <string>
#include "Pos.h"
#include <Box2D/Box2D.h>

/**
 * Clase Abrstracta (no se pueden crear instancias de la misma) que sirve de base para
 * 	los demas objetos que hereden de ella. Es una interfaz
 * 	Objetos que heredan: Circulo, Rectángulo, Poligono, Trapecio, Paralelogramo.
 */
class ObjetoMapa {
protected:
	bool estatico;
	std::string color;
	Pos* pos;
	int rot;
	int masa;
	float area;
	bool circulo = false;
	b2Body* linkAMundo;

public:
	void initialice(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa);

	bool esEstatico();

	bool esCirculo();

	float getDensidad();

	long getColor();
	void setColor(std::string c);

	Pos* getPos();
	void setPos(Pos* posicion);

	int getRotacion();
	void setRotacion(float rotacion);

	int getMasa();

	// getter y setter de link a mundo
	void setLinkAMundo(b2Body* link);
	b2Body* getLinkAMundo();

	//implementar
	virtual std::vector<Pos*>* getContorno() = 0;
	virtual	float getArea() = 0;

	virtual ~ObjetoMapa(){};
};

#endif /* OBJETOMAPA_H_ */
