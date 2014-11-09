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
	std::vector<MyContactListener*> vectorCuentaPasos;
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
	 *  Recibe un vector con la lista de eventos y uno con el id del personaje al que
	 *  pertencen, cada pos i debe tener correlacion entre los vectores.
	 */
	void cambiar(std::vector<std::vector<Evento>*> vectorDeListaDeEventos, std::vector<int> vectorDeID);

	std::vector<Personaje*> getPersonajes();
	std::vector<ObjetoMapa*> getObjetos();

	~Escenario();
};


#endif /* ESCENARIO_H_ */
