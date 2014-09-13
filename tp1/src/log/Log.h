#ifndef LOG_H_
#define LOG_H_
#include "../excepciones/LogExcepcion.h"

/**
 * Singleton, getInstance() siempre devuelve el mismo objeto Log.
 */
class Log {
protected:
	const char* archivo;
public:
	static const int LOG_ERR = 0;
	static const int LOG_WAR = 1;
	static const int LOG_DEB = 2;

	virtual void loguear(const char* mensaje, int LOG_TIPO) throw (LogExcepcion) = 0;
	virtual ~Log() {};
};

#endif /* LOG_H_ */
