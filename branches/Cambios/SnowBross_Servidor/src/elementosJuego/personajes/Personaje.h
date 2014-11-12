#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../ElementosJuego.h"
#include "../Pos.h"
#include <Box2D/Box2D.h>
#include "../objetos/Rectangulo.h"

class Personaje: public ElementosJuego {
public:
	enum E_PERFIL {
		DERECHA, IZQUIERDA
	};
	enum E_ACCION {
		QUIETO, DESPLAZANDO, SALTANDO, CAYENDO, EMPUJANDO
	};
	enum E_CON {
		CONECTADO, DESCONECTADO
	};
	struct Estado {
		E_PERFIL perfil;
		E_ACCION accion;
		E_CON conexion;

		bool operator==(const Estado& e) {
			if (e.perfil == this->perfil && e.accion == this->accion)
				return true;
			return false;
		}
	};

private:
	int ancho;
	int alto;
	Estado estado;
	void crearContorno();
	void calcularArea();

public:
	Personaje(Pos posicion);

	/*
	 * Devuelve verdadero si el objeto no se puede mover
	 */
	bool esEstatico();

	/*
	 * Devuelve verdadero si el objeto es un circulo
	 */
	bool esCirculo();

	/*
	 * Getter para alto y ancho del personaje en unidades reales
	 */
	int getAlto();
	int getAncho();


	/*
	 * Getter y Setter de estado
	 */
	void setEstado(E_PERFIL p, E_ACCION a);
	void setEstado(Estado estado);
	void setConexion(E_CON con);
	Estado getEstado();

	/*
	 * Getter del ID (�nico por cada personaje)
	 */
	int getID();

	~Personaje();
};
#endif /* PERSONAJE_H_ */
