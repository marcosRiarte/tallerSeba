#include "../src/log/Log.h"
#include "../src/log/DebugLog.h"
#include "../src/log/WarningLog.h"
#include "../src/log/ErrorLog.h"
#include "../src/Constantes.h"

void runLogsTest(){
	Log* loguer;
	loguer = DebugLog::getInstance();
	loguer->loguear("DebugLogTest - Se le ingresa un Error", Log::LOG_ERR);
 	loguer->loguear("DebugLogTest - Se le ingresa un Warning", Log::LOG_WAR);
	loguer->loguear("DebugLogTest - Se le ingresa un Debug", Log::LOG_DEB);
	loguer = WarningLog::getInstance();
	loguer->loguear("WarningLogTest - Se le ingresa un Error", Log::LOG_ERR);
	loguer->loguear("WarningLogTest - Se le ingresa un Warning", Log::LOG_WAR);
	loguer->loguear("WarningLogTest - Se le ingresa un Debug, NO DEBERIA APARECER EN EL LOG", Log::LOG_DEB);
	loguer = ErrorLog::getInstance();
	loguer->loguear("ErrorLogTest - Se le ingresa un Error", Log::LOG_ERR);
	loguer->loguear("ErrorLogTest - Se le ingresa un Warning, NO DEBERIA APARECER EN EL LOG", Log::LOG_WAR);
	loguer->loguear("ErrorLogTest - Se le ingresa un Debug, NO DEBERIA APARECER EN EL LOG", Log::LOG_DEB);
}

