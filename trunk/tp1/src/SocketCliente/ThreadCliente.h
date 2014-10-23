#include <windows.h>
#ifndef THREADCLIENTE_H_
#define THREADCLIENTE_H_

class ThreadCliente {

private:
	HANDLE thread;
	static void* start_routine(void*);

public:
	ThreadCliente();
	virtual ~ThreadCliente();
	void* detectar_bloqueo();

	int ejecutar();
	void salir();
	virtual void* correr()=0;

};

#endif /* THREADCLIENTE_H_ */
