/*
 * Maneja la relación entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include "../controlador/Evento.h"
#include "../parseo/Config.h"
#include "MyContactListener.h"

// Constantes del mundo en Box2D
static const float
GRAVEDAD_X = 0,
GRAVEDAD_Y = -50,
MEDIO_ALTO_SUELO = 2,
MEDIO_ALTO_TECHO = 1,
MEDIO_ANCHO_PARED = 2,
DENSIDAD_DEL_PERSONAJE = 0.31,
FRICCION_DEL_PERSONAJE = 0.4,
FRICCION_DE_OBJETO = 0.4,
FRICCION_CERO = 0.4,
IMPULSO_IZQ_X = -5000,
IMPULSO_IZQ_Y = 0,
IMPULSO_DER_X = 5000,
IMPULSO_DER_Y = 0,
IMPULSO_ARR_X = 0,
IMPULSO_ARR_Y = 650000;
static const float32 TIME_STEP = 1/60.0;
static const int32 VELOCITY_ITERATIONS = 8;
static const int32 POSITION_ITERATIONS = 3;

class Escenario {
private:
	std::vector<Personaje*>* personajes;
	std::vector<ObjetoMapa*>* objetos;
	MyContactListener* cuentaPasos;
	b2World* mundo;

public:
	/*
	 * Crea el escenario a partir de una configuracion
	 */
	Escenario(Config* config);

	/*
	 * Genera un nuevo de step, pone a los personajes en sus nuevas posiciones
	 */
	void cambiar(std::vector<Evento*>* ListaDeEventos);

	~Escenario();
};


#endif /* ESCENARIO_H_ */
