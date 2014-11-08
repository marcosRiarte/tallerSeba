#include "LogExcepcion.h"

LogExcepcion::LogExcepcion() {
	msg = nullptr;
}

LogExcepcion::LogExcepcion(const char* desc) {
	msg = desc;
}

const char* LogExcepcion::what(){
	return msg;
}

LogExcepcion::~LogExcepcion() {
	// TODO Auto-generated destructor stub
}
