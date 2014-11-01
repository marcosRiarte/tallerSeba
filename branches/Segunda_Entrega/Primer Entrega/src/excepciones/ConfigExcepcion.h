#ifndef CONFIGEXCEPCION_H_
#define CONFIGEXCEPCION_H_
#include <exception>

class Config_Excepcion: public std::exception{
private:
	const char *msg;
public:
	Config_Excepcion();
	Config_Excepcion(const char* desc);
	const char* what();
	virtual ~Config_Excepcion();
};

#endif /* CONFIGEXCEPCION_H_ */
