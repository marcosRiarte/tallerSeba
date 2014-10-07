#include "WarningLog.h"
#include "../Constantes.h"
#include <fstream>
#include <time.h>

WarningLog::WarningLog() {
	std::string dir = PATH_LOG;
	this->archivo = dir.append("warning_log.txt");
	fecha = nullptr;
}

WarningLog* WarningLog::instance = nullptr;

WarningLog* WarningLog::getInstance() {
	if (instance == nullptr) {
		instance = new WarningLog();
	}
	return instance;
}

void WarningLog::loguear(const char* mensajeError, Log::LOG_TIPO tipo) throw(LogExcepcion) {
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
		tipoDeLog = "Error - ";
		break;
	case (LOG_WAR):
		tipoDeLog = "Warning - ";
		break;
	default:
		return;
	}
	std::ofstream salida(archivo, std::ios::out | std::ios::app);
	if (!salida.is_open())
		throw new LogExcepcion("No se puede abrir el archivo de Log para Warnings \n");
	salida << tipoDeLog << mensajeError << "\n";
	salida.close();
}

WarningLog::~WarningLog() {
	// TODO Auto-generated destructor stub
}

