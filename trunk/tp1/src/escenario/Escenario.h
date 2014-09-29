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
static const float IMPULSO_IZQ_X = -1;
static const float IMPULSO_IZQ_Y = 0;
static const float IMPULSO_DER_X = 1;
static const float IMPULSO_DER_Y = 0;
static const float IMPULSO_ARR_X = 0;
static const float IMPULSO_ARR_Y = 65;
static const float32 TIME_STEP = 1/60.0;
static const int32 VELOCITY_ITERATIONS = 8;
static const int32 POSITION_ITERATIONS = 3;

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
