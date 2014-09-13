#include "DebugLog.h"
#include "../Constantes.h"
#include <fstream>

DebugLog::DebugLog() {
	std::string dir = PATH_LOG;
	this->archivo = dir.append("debug_log.txt").c_str();
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
	switch (tipo) {
	case (LOG_ERR):
		tipoDeLog = "Error - ";
		break;
	case (LOG_DEB):
		tipoDeLog = "Debug - ";
		break;
	case (LOG_WAR):
		tipoDeLog = "Warning - ";
		break;
	default:
		return;
	}
	std::ofstream salida(archivo, std::ios::out | std::ios::app);
	if (!salida.is_open())
		throw new LogExcepcion("No se puede abrir el archivo de Log para Debug \n");
	salida << tipoDeLog << mensajeError << "\n";
	salida.close();
}

DebugLog::~DebugLog() {
	// TODO Auto-generated destructor stub
}

