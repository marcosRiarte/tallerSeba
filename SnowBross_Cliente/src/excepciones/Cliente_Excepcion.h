#ifndef CLIENTE_EXCEPCION_H_
#define CLIENTE_EXCEPCION_H_

#include <exception>
#include <string>

class Cliente_Excepcion: public std::exception {
private:
	const char *msg;
public:
	Cliente_Excepcion();
	Cliente_Excepcion(const char *desc);
	Cliente_Excepcion(std::string desc);
	const char* what();
	virtual ~Cliente_Excepcion();
};

#endif /* CLIENTE_EXCEPCION_H_ */
