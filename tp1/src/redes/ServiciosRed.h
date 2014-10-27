#ifndef SERVICIOSRED_H_
#define SERVICIOSRED_H_

#pragma once
#include <winsock2.h>
#include <Windows.h>

class ServiciosRed {
public:
	static int enviarMensaje(SOCKET SocketActual, char * mensaje, int tamanioMensaje);
	static int recibirMensaje(SOCKET SocketActual, char * buffer, int tamBuffer);
};

#endif /* SERVICIOSRED_H_ */
