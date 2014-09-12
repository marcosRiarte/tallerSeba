#include "ErrorLog.h"

ErrorLog::ErrorLog() {
	std::ofstream fs("nombre.txt");
}

void ErrorLog::Loguear(std::string mensajeError, int tipo ) {
	std::ofstream salida;
	if !(salida.is_open())
		salida.open(archivo);
	salida << mensajeError + nombreArchivo << "\n";
}


ErrorLog::~ErrorLog() {
	// TODO Auto-generated destructor stub
}

