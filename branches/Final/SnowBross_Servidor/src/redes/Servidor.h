#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include<winsock2.h>

#include "Paquetes.h"
#include "../excepciones/Servidor_Excepcion.h"

#define MAX_CANTIDAD_CONEXIONES 5
#define PUERTO 9999

class Servidor {
private:
	static WSADATA wsa;
	static SOCKET sockfd;
	static struct sockaddr_in local;
	static int len;

	Servidor();
public:
	static unsigned int conexionesEstablecidas;
	static SOCKET sock[MAX_CANTIDAD_CONEXIONES];

	static void iniciar(unsigned int cantidadConexiones) throw (Servidor_Excepcion);
	static PaqueteAServidor recibir();
	static void enviar(SOCKET socketDest, PaqueteACliente p) throw (Servidor_Excepcion);
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
