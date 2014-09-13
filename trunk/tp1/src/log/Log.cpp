#include "Log.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>

void Log::Loguear(std::string mensajeError, std::string nombreArchivo) {
	std::string salidaStr = "tpTaller_Log.txt";
	std::ofstream salida;
	salida.open(salidaStr.c_str());
	salida << mensajeError + nombreArchivo << "\n";
}

