#include "DebugLog.h"
#include "../Constantes.h"
#include <fstream>
#include <time.h>

DebugLog::DebugLog() {
//	std::string dir = PATH_LOG;
//	archivo = dir.append("debug_log.txt").c_str();
	fecha = nullptr;
}

DebugLog* DebugLog::instance = nullptr;

DebugLog* DebugLog::getInstance() {
	if (instance == nullptr) {
		instance = new DebugLog();
	}
	return instance;
}

void DebugLog::loguear(const char* mensajeError, Log::LOG_TIPO tipo) throw(LogExcepcion) {
	const char * tipoDeLog;
	time_t t;
	struct tm * timestamp;

	time(&t);
	timestamp = localtime(&t);
	std::string fechaAux = asctime(timestamp);
	fechaAux.pop_back();
	fecha = fechaAux.c_str();

	switch (tipo) {
	case (LOG_ERR):
		tipoDeLog = " - Error - ";
		break;
	case (LOG_DEB):
		tipoDeLog = " - Debug - ";
		break;
	case (LOG_WAR):
		tipoDeLog = " - Warning - ";
		break;
	default:
		return;
	}
	archivo = "./logs/debug.txt";
	std::ofstream salida(archivo, std::ios::out | std::ios::app);
	if (!salida.is_open())
		throw new LogExcepcion("No se puede abrir el archivo de Log para Debug \n");
	salida << fecha << tipoDeLog << mensajeError << "\n";
	salida.close();
}

DebugLog::~DebugLog() {
	// TODO Auto-generated destructor stub
}

