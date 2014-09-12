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
	ErrorLog();
public:
	ErrorLog* getInstance();
	void Loguear(char * mensaje, int tipo);
	virtual ~ErrorLog();
};

#endif /* ERRORLOG_H_ */
