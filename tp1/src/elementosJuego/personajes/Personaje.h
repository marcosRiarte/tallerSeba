#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../ElementosJuego.h"
#include "../Pos.h"
#include <Box2D/Box2D.h>
#include "../objetos/Rectangulo.h"

class Personaje : public ElementosJuego {
public:
	/*
	enum E_PERFIL {DERECHA, IZQUIERDA};
	enum E_ACCION {QUIETO, DESPLAZANDO, SALTANDO, CAYENDO, EMPUJANDO};
	struct Estado{
		E_PERFIL perfil;
		E_ACCION accion;
	};
	*/
	std::string estado;
private:
	int ancho;
	int alto;
	/*
	Estado* estado;
	*/
	Rectangulo *rectanguloPersonaje; //Solo para pruebas

public:

	/*
	 * Devuelve el area del elemento
	 */
	float getArea();

	Personaje(Pos* posicion);

	// getters de dimensiones
	int getAlto();
	int getAncho();

	// devuelve verdadero si esta en esa posicion
	bool estaEnPos(Pos* posicion);

	std::vector<Pos*>* getContorno();
	Rectangulo* getRectangulo();


	void setPos(Pos* posicion);

	/*
	// getter y setter de estado
	void setEstado(E_PERFIL p, E_ACCION a);
	void setEstado(Estado estado);
	Estado getEstado();
*/
	//Setters y getters de estado.
	void setEstado(std::string unEstado);
	std::string getEstado();

	~Personaje();
};

#endif /* PERSONAJE_H_ */
