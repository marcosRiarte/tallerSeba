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

// Log
#define PATH_LOG				 	".\\logs\\";
static Log* loguer = (Log*) DebugLog::getInstance();

#endif /* CONSTANTES_H_ */
