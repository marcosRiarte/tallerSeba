#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../ElementosJuego.h"
#include "../Pos.h"
#include <Box2D/Box2D.h>
#include "../objetos/Rectangulo.h"

class Personaje : public ElementosJuego {
public:

	enum E_PERFIL {DERECHA, IZQUIERDA};
	enum E_ACCION {QUIETO, DESPLAZANDO, SALTANDO, CAYENDO, EMPUJANDO};
	struct Estado{
		E_PERFIL perfil;
		E_ACCION accion;
	};
/*
	std::string estado;*/
private:
	int ancho;
	int alto;

	Estado* estado;

	Rectangulo *rectanguloPersonaje; //Solo para pruebas

public:

	Personaje(Pos* posicion);

	/*
	 * Devuelve el area del elemento
	 */
	float getArea();

	/*
	 * Getter para alto y ancho del personaje en unidades reales
	 */
	int getAlto();
	int getAncho();

	/*
	 * Setter para la posicion
	 */
	void setPos(Pos* posicion);

	/*
	 * Devuelve el contorno del personaje
	 */
	std::vector<Pos*>* getContorno();

	/*
	 * Devuelve el rectangulo que representa al personaje
	 */
	Rectangulo* getRectangulo();


	// getter y setter de estado
	void setEstado(E_PERFIL p, E_ACCION a);
	void setEstado(Estado estado);
	Estado getEstado();


	/*
	 * Getter y setter para el estado
	 */
	/*void setEstado(std::string unEstado);
	std::string getEstado();
*/
	~Personaje();
};

#endif /* PERSONAJE_H_ */
