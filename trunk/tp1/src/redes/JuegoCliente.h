#include <winsock2.h>
#include <Windows.h>
#include "RedCliente.h"

#ifndef JUEGOCLIENTE_H_
#define JUEGOCLIENTE_H_

class JuegoCliente {
public:
	JuegoCliente();
	virtual ~JuegoCliente();
	RedCliente* red;
};

#endif /* JUEGOCLIENTE_H_ */
