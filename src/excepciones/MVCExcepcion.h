/*
 * MVCExcepcion.h
 *
 *  Created on: 6/10/2014
 *      Author: Seba
 */

#ifndef MVCEXCEPCION_H_
#define MVCEXCEPCION_H_

#include <exception>

class MVC_Excepcion: public std::exception {
private:
	const char *msg;
public:
	MVC_Excepcion();
	MVC_Excepcion(const char* desc);
	const char* what();
	virtual ~MVC_Excepcion();
};

#endif /* MVCEXCEPCION_H_ */
