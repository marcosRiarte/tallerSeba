#ifndef CONSTANTES_H_
#define CONSTANTES_H_
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

static int rmask = 0xff000000;
static int gmask = 0x00ff0000;
static int bmask = 0x0000ff00;
static int amask = 0x000000ff;

#endif /* CONSTANTES_H_ */
