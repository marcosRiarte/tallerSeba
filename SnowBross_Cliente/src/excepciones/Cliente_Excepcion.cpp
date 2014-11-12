#include "Cliente_Excepcion.h"

Cliente_Excepcion::Cliente_Excepcion() {
	msg = nullptr;
}

Cliente_Excepcion::Cliente_Excepcion(const char* desc) {
	msg = desc;
}

Cliente_Excepcion::Cliente_Excepcion(std::string desc) {
	msg = desc.c_str();
}

const char* Cliente_Excepcion::what(){
	return msg;
}

Cliente_Excepcion::~Cliente_Excepcion() {
	// TODO Auto-generated destructor stub
}

