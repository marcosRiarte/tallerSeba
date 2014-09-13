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
	static const int teclaNada = 0;
	static const int teclaIzquierda = 1;
	static const int teclaDerecha = 2;
	static const int teclaArriba = 3;

	// se crea por defecto con "teclaNada"
	Evento();
	Evento(int tecla);

	// geter y seter para la tecla
	void setTecla(int tecla);
	int getTecla();

	virtual ~Evento();
};


#endif /* EVENTO_H_ */
