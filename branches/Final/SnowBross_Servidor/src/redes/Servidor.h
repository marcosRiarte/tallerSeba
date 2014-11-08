#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include<winsock2.h>

#include "Paquetes.h"

class Servidor {
private:
	static WSADATA wsa;
	static SOCKET sock;
	static struct sockaddr_in local;
	static int len;

public:
	static void iniciar();
	static PaqueteAServidor recibir();
	static void enviar(PaqueteACliente p);
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
