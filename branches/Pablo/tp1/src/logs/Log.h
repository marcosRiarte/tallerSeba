#ifndef LOG_H_
#define LOG_H_
#include <string>

/**
 * Singleton, getInstance() siempre devuelve el mismo objeto Log.
 */
class Log {
private:
	Log* instance;
	const char* archivo;
public:
	virtual Log* getInstance();
	virtual void Loguear(char * mensaje, int tipo);
};

#endif /* LOG_H_ */
