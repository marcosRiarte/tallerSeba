/*
 * SDLExcepcion.h
 *
 *  Created on: 11/9/2014
 *      Author: pablo_000
 */

#ifndef SDLEXCEPCION_H_
#define SDLEXCEPCION_H_

#include <exception>

class SDL_Excepcion: public std::exception {
private:
	const char *msg;
public:
	SDL_Excepcion();
	SDL_Excepcion(const char *desc);
	const char* what();
	virtual ~SDL_Excepcion();
};

#endif /* SDLEXCEPCION_H_ */
