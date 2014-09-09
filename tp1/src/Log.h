#ifndef LOG_H_
#define LOG_H_
#include <string>

class Log {
public:
	static void Loguear(std::string mensajeError, std::string nombreArchivo);
};

#endif /* LOG_H_ */
