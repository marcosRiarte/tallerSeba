#ifndef SDLEXCEPCION_H_
#define SDLEXCEPCION_H_

#include <exception>
#include <string>

class SDL_Excepcion: public std::exception {
private:
	const char *msg;
public:
	SDL_Excepcion();
	SDL_Excepcion(const char *desc);
	SDL_Excepcion(std::string desc);
	const char* what();
	virtual ~SDL_Excepcion();
};

#endif /* SDLEXCEPCION_H_ */
