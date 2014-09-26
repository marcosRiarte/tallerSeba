/* Maneja la relación entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "../personajes/Personaje.h"
#include "../objetos/ObjetoMapa.h"
#include "../entrada/Evento.h"
#include "../parseo/Config.h"
#include <Box2D/Box2D.h>

static const float gravedadX = 0;
static const float gravedadY = -10;
static const float medioAltoSuelo = 5;
static const float medioAltoTecho = 3;
static const float medioAnchoPared = 4;
static const float medioAnchoPlayer = 5;
static const float medioAltoPlayer = 10;
static const float densidadDelPersonaje = 10;
static const float friccionDelPersonaje = 10;
static const float friccionDeObjetos = 10;
static const float32 timeStep = 1.0f / 60.0f;
static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

class Escenario {
private:
	std::vector<Personaje*>* personajes;
	std::vector<ObjetoMapa*>* objetos;
	Pantalla* pantalla;
	b2World* mundo;

public:
	Escenario(Config* config);

	// Genera un nuevo de step, pone a los personajes en sus nuevas posiciones,
	// avisando si cambiar en relación a su posición anterior.
	void cambiar(std::vector<Evento*>* ListaDeEventos);

	virtual ~Escenario();
};


#endif /* ESCENARIO_H_ */
