#ifndef WARNINGLOG_H_
#define WARNINGLOG_H_

#include "Log.h"

class WarningLog: public Log {
private:
	const char* fecha;
	static WarningLog* instance;
	WarningLog();
public:
	static WarningLog* getInstance();
	void loguear(const char* mensaje, Log::LOG_TIPO tipo) throw (LogExcepcion);
	virtual ~WarningLog();
};

#endif /* WARNINGLOG_H_ */
