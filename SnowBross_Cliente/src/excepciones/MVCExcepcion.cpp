/*
 * MVCExcepcion.cpp
 *
 *  Created on: 6/10/2014
 *      Author: Seba
 */

#include "MVCExcepcion.h"

MVC_Excepcion::MVC_Excepcion() {
	msg = nullptr;
}
MVC_Excepcion::MVC_Excepcion(const char* desc) {
	msg = desc;
}

const char* MVC_Excepcion::what(){
	return msg;
}

MVC_Excepcion::~MVC_Excepcion() {
	// TODO Auto-generated destructor stub
}

