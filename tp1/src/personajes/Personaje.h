#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../objetos/Pos.h"
#include <Box2D/Box2D.h>
#include "../objetos/Rectangulo.h"

class Personaje {
public:
	enum E_PERFIL {DERECHA, IZQUIERDA};
	enum E_MOVIMIENTO {QUIETO, MOVIMIENTO, SALTANDO_SUBIENDO, SALTANDO_BAJANDO};
	enum E_ACCION {NINGUNA, EMPUJANDO};
	struct Estado{
		E_PERFIL perfil;
		E_MOVIMIENTO movimiento;
		E_ACCION accion;
	};

private:
	int ancho;
	int alto;
	Pos* pos;
	float rot;
	b2Body* linkAMundo;
	Estado estado;

	Rectangulo *rectanguloPersonaje; //Solo para pruebas

	bool miraALaIzq;
	int estado;
	bool vaParaArriba;
	// Estados posibles:
	#define QUIETO				0
	#define SALTANDO			1
	#define EN_MOVIMIENTO		2


public:
	Personaje(Pos* posicion);

	//getters y setters del estado
	bool getMiraALaIzq();
	int getEstado();
	bool getVaParaArriba();
	void setMiraALaIzq(bool);
	void setEstado(int);
	void setVaParaArriba(bool);


	// getters de dimensiones
	int getAlto();
	int getAncho();

	// getter y setter de la posicion
	void setPosicion(Pos* posicion);
	Pos* getPosicion();

	// devuelve verdadero si esta en esa posicion
	bool estaEnPos(Pos* posicion);

	std::vector<Pos*>* getContorno();
	Rectangulo* getRectangulo();

	// getter y setter de estado
	void setEstado(E_PERFIL p, E_MOVIMIENTO m, E_ACCION a);
	void setEstado(E_PERFIL p, E_MOVIMIENTO m);
	void setEstado(Estado estado);
	Estado getEstado();

	// getter y setter de link a mundo
	void setLinkAMundo(b2Body* link);
	b2Body* getLinkAMundo();

	virtual ~Personaje();
};

#endif /* PERSONAJE_H_ */
