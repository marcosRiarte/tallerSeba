#include "ErrorLog.h"
#include "../Constantes.h"
#include <fstream>
#include <exception>

ErrorLog::ErrorLog() {
	std::string dir = PATH_LOG;
	this->archivo = dir.append("error_log.txt").c_str();
}

ErrorLog* ErrorLog::instance = nullptr;

ErrorLog* ErrorLog::getInstance() {
	if (instance == nullptr) {
		instance = new ErrorLog();
	}
	return instance;
}

void ErrorLog::loguear(const char* mensajeError, int LOG_TIPO) throw (LogExcepcion) {
	if (LOG_TIPO == LOG_ERR) {
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

