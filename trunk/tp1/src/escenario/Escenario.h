/* Maneja la relación entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "../personajes/Personaje.h"
#include "../objetos/ObjetoMapa.h"
#include "../entrada/Evento.h"

class Escenario {
private:
	std::vector<Personaje> personajes;
	std::vector<ObjetoMapa> objetos;

public:
	Escenario(std::vector<Personaje> e_personajes,std::vector<ObjetoMapa> e_objetos);

	// Genera un nuevo de step, pone a los personajes en sus nuevas posiciones,
	// avisando si cambiar en relación a su posición anterior.
	void cambiar(Evento evento);

	virtual ~Escenario();
};


#endif /* ESCENARIO_H_ */
