#ifndef REDCLIENTE_H_
#define REDCLIENTE_H_
#define WIN32_LEAN_AND_MEAN



#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "ServiciosRed.h"


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

// Tamanio del buffer
#define DEFAULT_BUFLEN 512
// puerto a usar para las conexiones
#define DEFAULT_PORT "6881"


class RedCliente {
public:
	RedCliente(void);
	virtual ~RedCliente(void);
    // para chequeo de errores
    int resultado;
    int recibirPaquetes(char *);
    // socket para el cliente
    SOCKET ConectarSocket;

};

#endif /* REDCLIENTE_H_ */
