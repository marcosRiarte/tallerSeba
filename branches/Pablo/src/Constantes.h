#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#include "log/Log.h"
#include "log/DebugLog.h"
#include "log/WarningLog.h"
#include "log/ErrorLog.h"

// Salida del main
#define RES_OK	          			0
#define RES_AYUDA		  			1
#define RES_ERR						-1

// Salida del gameloop
#define FIN_DEL_JUEGO				0
#define REINICIAR					1
#define CONTINUAR					2

// Log
#define PATH_LOG				 	"./logs/"
static Log* loguer = (Log*) DebugLog::getInstance();

// Datos del personaje
#define ANCHO_PERSONAJE_UN			34
#define ALTO_PERSONAJE_UN			45
#define MASA_PERSONAJE				460

// Constantes del mundo en Box2D
#define GRAVEDAD_X 					0
#define GRAVEDAD_Y					-50
#define GROSOR_BORDE_MUNDO			4
#define FRICCION_DEL_PERSONAJE		0.4
#define FRICCION_DE_OBJETO			0.4
#define DENSIDAD_CERO				0
#define IMPULSO_IZQ_X				-5000
#define IMPULSO_IZQ_Y				0
#define IMPULSO_DER_X				5000
#define IMPULSO_DER_Y				0
#define IMPULSO_ARR_X				0
#define IMPULSO_ARR_Y				650000
#define TIME_STEP					1/60.0
#define VELOCITY_ITERATIONS			8
#define POSITION_ITERATIONS			3

// Constantes de SDL
#define FRAME_RATE					4
#endif /* CONSTANTES_H_ */
