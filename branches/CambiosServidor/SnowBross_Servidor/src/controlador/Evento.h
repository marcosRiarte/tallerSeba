/*
 * Representa un evento de entrada
 */

#ifndef EVENTO_H_
#define EVENTO_H_

class Evento {
private:
	int teclaIngresada;

public:
	// Valores posibles para la tecla ingresada:
#define TECLA_NADA					0
#define TECLA_IZQUIERDA				1
#define TECLA_DERECHA				2
#define TECLA_ARRIBA				3

	// se crea por defecto con "teclaNada"
	Evento();
	Evento(int evento);

	// geter y seter para la tecla
	void setTecla(int tecla);
	int getTecla();
	void procesarTecla(int tecla);

	virtual ~Evento();
};

#endif /* EVENTO_H_ */
