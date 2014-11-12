#ifndef LOG_H_
#define LOG_H_
#include "../excepciones/LogExcepcion.h"
#include <string>

/**
 * Singleton, getInstance() siempre devuelve el mismo objeto Log.
 */
class Log {
protected:
	std::string archivo;
public:
	enum LOG_TIPO {LOG_ERR, LOG_WAR, LOG_DEB};

	virtual void loguear(const char* mensaje, LOG_TIPO tipo) throw (LogExcepcion) = 0;
	virtual void loguear(std::string mensaje, LOG_TIPO tipo) throw (LogExcepcion) = 0;
	virtual ~Log() {};
};

#endif /* LOG_H_ */
