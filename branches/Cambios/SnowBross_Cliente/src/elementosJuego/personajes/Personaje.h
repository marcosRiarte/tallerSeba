#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include "../ElementosJuego.h"

class Personaje: public ElementosJuego {
public:
	enum E_PERFIL {
		DERECHA, IZQUIERDA
	};
	enum E_ACCION {
		QUIETO, DESPLAZANDO, SALTANDO, CAYENDO, EMPUJANDO, DESCONECTADO
	};
	struct Estado {
		E_PERFIL perfil;
		E_ACCION accion;

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

public:
	Personaje();
	Personaje(Pos posicion);

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
	Estado getEstado();

	~Personaje();
};
#endif /* PERSONAJE_H_ */
