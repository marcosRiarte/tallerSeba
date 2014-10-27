/*
 * RedServidor.h
 *
 *  Created on: 27/10/2014
 *      Author: Seba
 */

#ifndef REDSERVIDOR_H_
#define REDSERVIDOR_H_

#include <winsock2.h>
#include <Windows.h>
#include "ServiciosRed.h"
#include <ws2tcpip.h>
#include <map>
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881"


#ifdef __cplusplus
extern "C" {
#endif
   void WSAAPI freeaddrinfo( struct addrinfo* );

   int WSAAPI getaddrinfo( const char*, const char*, const struct addrinfo*,
                 struct addrinfo** );

   int WSAAPI getnameinfo( const struct sockaddr*, socklen_t, char*, DWORD,
                char*, DWORD, int );
#ifdef __cplusplus
}
#endif



class RedServidor {
public:
	RedServidor(void);
	virtual ~RedServidor(void);

	 // Socket para escuchar nuevas conexiones
	    SOCKET SocketEscuchar;

	    // Socket a darle a los clientes
	    SOCKET SocketCliente;

	    // para chequeo de errores
	    int resultado;

	    // tabla para seguir cada socket de cliente
	    std::map<unsigned int, SOCKET> sesiones;

	    // aceptar nuevas conexiones
	    bool aceptarCliente(unsigned int & id);
};

#endif /* REDSERVIDOR_H_ */
