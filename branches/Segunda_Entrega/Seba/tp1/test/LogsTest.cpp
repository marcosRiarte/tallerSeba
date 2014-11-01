#include "../src/Constantes.h"

void runLogsTest(){
	loguer->loguear("LogTest - Se le ingresa un Error", Log::LOG_TIPO::LOG_ERR);
 	loguer->loguear("LogTest - Se le ingresa un Warning", Log::LOG_TIPO::LOG_WAR);
	loguer->loguear("LogTest - Se le ingresa un Debug", Log::LOG_TIPO::LOG_DEB);
}

