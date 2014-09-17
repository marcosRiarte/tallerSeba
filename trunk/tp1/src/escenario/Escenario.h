/* Maneja la relación entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "../personajes/Personaje.h"
#include "../objetos/ObjetoMapa.h"
#include "../entrada/Evento.h"
#include <Box2D/Box2D.h>

static const float gravedadX = 0;
static const float gravedadY = -10;
static const float posSueloX = 0;
static const float posSueloY = -10;
static const float medioAnchoSuelo = 50;
static const float medioAltoSuelo = 10;
static const float medioAnchoPlayer = 5;
static const float medioAltoPlayer = 10;
static const float masaDelPersonaje = 10;

class Escenario {
private:
	std::vector<Personaje>* personajes;
	std::vector<ObjetoMapa>* objetos;
	b2World* carla;

public:
	Escenario(std::vector<Personaje>* e_personajes, std::vector<ObjetoMapa>* e_objetos);

	// Genera un nuevo de step, pone a los personajes en sus nuevas posiciones,
	// avisando si cambiar en relación a su posición anterior.
	void cambiar(Evento evento);

	virtual ~Escenario();
};


#endif /* ESCENARIO_H_ */
