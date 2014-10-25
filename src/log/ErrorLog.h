/*
 * ErrorLog.h
 *
 *  Created on: 12/9/2014
 *      Author: pgotuzzo
 */

#ifndef ERRORLOG_H_
#define ERRORLOG_H_

#include "Log.h"

class ErrorLog: public Log {
private:
	const char* fecha;
	static ErrorLog* instance;
	ErrorLog();
public:
	static ErrorLog* getInstance();
	void loguear(const char* mensaje, Log::LOG_TIPO tipo) throw (LogExcepcion);
	virtual ~ErrorLog();
};

#endif /* ERRORLOG_H_ */
