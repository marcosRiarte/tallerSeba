#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../objetos/Pos.h"
#include <Box2D/Box2D.h>
#include "../objetos/Rectangulo.h"

class Personaje {
private:
	Pos* pos;
	b2Body* linkAMundo;
	float rot;
	int ancho;
	int alto;
	Rectangulo *rectanguloPersonaje;
public:
	Personaje(Pos* posicion);

	// getter y setter de la posicion
	void setPosicion(Pos* posicion);
	Pos* getPosicion();
	std::vector<Pos*>* getContorno();
	Rectangulo* getRectangulo();

	// getter y setter de link a mundo
	void setLinkAMundo(b2Body* link);
	b2Body* getLinkAMundo();

	// devuelve verdadero si esta en esa posicion
	bool estaEnPos(Pos* posicion);

	virtual ~Personaje();
};

#endif /* PERSONAJE_H_ */
