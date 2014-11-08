#ifndef CONEXION_H_
#define CONEXION_H_

#include <winsock2.h>
#include "Paquetes.h"

class Conexion {
private:
	//Esta relacionado con la versión a utilizar y la inicializacion de winsock.
	WSADATA wsa;

	//Socket a utilizar.
	SOCKET sock;

	//Los siguientes atributos se encargan de manejar los datos del servidor al que nos vamos a conectar y le  tipo de conexion que vamos a hacer (TCP/IP)
	//hostent es un struct ya definido que contiene toda la información a bajo nivel sobre el host al que vayamos a conectar.
	struct hostent *host;
	//sockaddr_in es un struct ya definido que contendrá la información final de la dirección a la que vamos a conectar.
	struct sockaddr_in direc;

	int bytesRecibidos;
	PaqueteACliente paquete;

public:
	Conexion();
	PaqueteACliente recibir();
	void enviar(PaqueteAServidor p);
	virtual ~Conexion();
};

#endif /* CONEXION_H_ */
