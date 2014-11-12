#ifndef SERVIDOR_EXCEPCION_H_
#define SERVIDOR_EXCEPCION_H_

#include <exception>

class Servidor_Excepcion: public std::exception {
private:
	const char *msg;
public:
	Servidor_Excepcion();
	Servidor_Excepcion(const char *desc);
	const char* what();
	virtual ~Servidor_Excepcion();
};

#endif /* SERVIDOR_EXCEPCION_H_ */
