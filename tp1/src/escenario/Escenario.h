/* Maneja la relación entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "../personajes/Personaje.h"
#include "../objetos/ObjetoMapa.h"
#include "../entrada/Evento.h"
#include "../parseo/Config.h"
#include <Box2D/Box2D.h>

static const float GRAVEDAD_X = 0;
static const float GRAVEDAD_Y = -10;
static const float MEDIO_ALTO_SUELO = 5;
static const float MEDIO_ALTO_TECHO = 3;
static const float MEDIO_ANCHO_PARED = 4;
static const float MEDIO_ANCHO_PERSONAJE = 5;
static const float MEDIO_ALTO_PERSONAJE = 10;
static const float DENSIDAD_DEL_PERSONAJE = 10;
static const float FRICCION_DEL_PERSONAJE = 10;
static const float FRICCION_DE_OBJETO = 10;
static const float DENSIDAD_CERO = 0;
static const float32 TIME_STEP = 1.0f / 60.0f;
static const int32 VELOCITY_ITERATIONS = 6;
static const int32 POSITION_ITERATIONS = 2;

class Escenario {
private:
	std::vector<Personaje*>* personajes;
	std::vector<ObjetoMapa*>* objetos;
	b2World* mundo;

public:
	Escenario(Config* config);

	// Genera un nuevo de step, pone a los personajes en sus nuevas posiciones,
	// avisando si cambiar en relación a su posición anterior.
	void cambiar(std::vector<Evento*>* ListaDeEventos);

	~Escenario();
};


#endif /* ESCENARIO_H_ */
