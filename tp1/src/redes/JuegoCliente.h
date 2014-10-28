#include <winsock2.h>
#include <Windows.h>
#include "RedCliente.h"
#include "DatosRed.h"

#ifndef JUEGOCLIENTE_H_
#define JUEGOCLIENTE_H_

class JuegoCliente {
public:
	JuegoCliente();
	virtual ~JuegoCliente();
	RedCliente* red;

    void enviarPaquetesAccion();

    char network_data[MAX_PACKET_SIZE];

    void actualizar();

};

#endif /* JUEGOCLIENTE_H_ */
