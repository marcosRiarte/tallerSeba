/*
 * Maneja la relación entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "../controlador/Evento.h"
#include "../parseo/Config.h"
#include "MyContactListener.h"

class Escenario {
private:
	std::vector<Personaje*> personajes;
	std::vector<ObjetoMapa*> objetos;
	MyContactListener* cuentaPasos;
	b2World* mundo;

public:
	/*
	 * Crea el escenario a partir de una configuracion que contiene la lista de objetos
	 * y personajes a crear, y los parametros de tamaño del mundo.
	 */
	Escenario(Config* config);

	/*
	 * Toma los eventos de entrada, aplica los cambios al mundo y pone a los personajes
	 *  en sus nuevas posiciones
	 */

	void cambiar(std::vector<Evento>* ListaDeEventos);

	~Escenario();
};


#endif /* ESCENARIO_H_ */
