#include "ConfigExcepcion.h"

Config_Excepcion::Config_Excepcion() {
	msg = nullptr;
}

Config_Excepcion::Config_Excepcion(const char* desc) {
	msg = desc;
}

const char* Config_Excepcion::what(){
	return msg;
}

Config_Excepcion::~Config_Excepcion() {
	// TODO Auto-generated destructor stub
}

