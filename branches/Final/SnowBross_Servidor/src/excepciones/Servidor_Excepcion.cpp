#include "Servidor_Excepcion.h"

Servidor_Excepcion::Servidor_Excepcion() {
	msg = nullptr;
}

Servidor_Excepcion::Servidor_Excepcion(const char* desc) {
	msg = desc;
}

const char* Servidor_Excepcion::what(){
	return msg;
}

Servidor_Excepcion::~Servidor_Excepcion() {
	// TODO Auto-generated destructor stub
}

