#include <windows.h>
#ifndef THREADSERVIDOR_H_
#define THREADSERVIDOR_H_

class ThreadServidor {

private:
	HANDLE thread;
	static void* start_routine(void*);

public:
	ThreadServidor();
	virtual ~ThreadServidor();

	//Es el join
	void* detectar_bloqueo();
	int ejecutar();
	void salir();
	virtual void* correr()=0;

};

#endif /* THREADSERVIDOR_H_ */
