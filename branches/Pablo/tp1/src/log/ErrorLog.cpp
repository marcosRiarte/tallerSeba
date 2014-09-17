#include "ErrorLog.h"
#include "../Constantes.h"
#include <fstream>
#include <exception>
#include <time.h>

ErrorLog::ErrorLog() {
	std::string dir = PATH_LOG;
	this->archivo = dir.append("error_log.txt").c_str();
	fecha = nullptr;
}

ErrorLog* ErrorLog::instance = nullptr;

ErrorLog* ErrorLog::getInstance() {
	if (instance == nullptr) {
		instance = new ErrorLog();
	}
	return instance;
}

void ErrorLog::loguear(const char* mensajeError, Log::LOG_TIPO tipo) throw (LogExcepcion) {
	if (tipo == LOG_ERR) {
		time_t t;
		struct tm * timestamp;

		time(&t);
		timestamp = localtime(&t);
		std::string fechaAux = asctime(timestamp);
		fechaAux.pop_back();
		fecha = fechaAux.c_str();

		std::ofstream salida(archivo, std::ios::out | std::ios::app);
		if (!salida.is_open())
			throw new LogExcepcion("No se puede abrir el archivo de Log para Errores \n");
		salida << "Error - " << mensajeError << "\n";
		salida.close();
	}
}

ErrorLog::~ErrorLog() {
	// TODO Auto-generated destructor stub
}

