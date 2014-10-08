/*
 * DebugLog.h
 *
 *  Created on: 12/9/2014
 *      Author: pablo_000
 */

#ifndef DEBUGLOG_H_
#define DEBUGLOG_H_

#include "Log.h"

class DebugLog: public Log {
private:
	const char * fecha;
	static DebugLog* instance;
	DebugLog();
public:
	static DebugLog* getInstance();
	void loguear(const char* mensaje, Log::LOG_TIPO tipo) throw (LogExcepcion);
	virtual ~DebugLog();
};

#endif /* DEBUGLOG_H_ */
