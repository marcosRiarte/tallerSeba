#ifndef LOGEXCEPCION_H_
#define LOGEXCEPCION_H_

#include <exception>

class LogExcepcion: public std::exception {
private:
	const char *msg;
public:
	LogExcepcion();
	LogExcepcion(const char* desc);
	const char* what();
	virtual ~LogExcepcion();
};

#endif /* LOGEXCEPCION_H_ */
