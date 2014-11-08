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

// Constantes de SDL
#define FRAME_RATE					4
#endif /* CONSTANTES_H_ */
