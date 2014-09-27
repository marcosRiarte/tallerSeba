/*
 * Representa un evento de entrada
 */

#ifndef EVENTO_H_
#define EVENTO_H_
#include <string>
#include <SDL2/SDL.h>

class Evento {
private:
	int teclaIngresada;

public:
	// Valores posibles para la tecla ingresada:
	static const int teclaNada = 0;
	static const int teclaIzquierda = 1;
	static const int teclaDerecha = 2;
	static const int teclaArriba = 3;
	static const int teclaR = 4;

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
