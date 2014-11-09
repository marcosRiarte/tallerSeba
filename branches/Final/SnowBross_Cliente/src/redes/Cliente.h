#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <winsock2.h>

#include "Paquetes.h"
#include "../excepciones/Cliente_Excepcion.h"

class Cliente {
private:
	//Esta relacionado con la versión a utilizar y la inicializacion de winsock.
	static WSADATA wsa;

	//Socket a utilizar.
	static SOCKET sock;

	//Los siguientes atributos se encargan de manejar los datos del servidor al que nos vamos a conectar y le  tipo de conexion que vamos a hacer (TCP/IP)
	//hostent es un struct ya definido que contiene toda la información a bajo nivel sobre el host al que vayamos a conectar.
	static struct hostent *host;
	//sockaddr_in es un struct ya definido que contendrá la información final de la dirección a la que vamos a conectar.
	static struct sockaddr_in direc;

	Cliente();
public:
	static void iniciar() throw (Cliente_Excepcion);
	static PaqueteACliente recibir() throw (Cliente_Excepcion);
	static void enviar(PaqueteAServidor p) throw (Cliente_Excepcion);
	virtual ~Cliente();
};

#endif /* CLIENTE_H_ */
