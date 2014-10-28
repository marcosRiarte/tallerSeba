/*
 * RedCliente.cpp
 *
 *  Created on: 27/10/2014
 *      Author: Seba
 */

#include "RedCliente.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include "DatosRed.h"

RedCliente::RedCliente(void) {

	// crea el objeto WSADATA
	WSADATA wsaData;

	// socket
	ConectarSocket = INVALID_SOCKET;

	// mantiene información de dirección para que el socket se conecte
	struct addrinfo *result = NULL, *ptr = NULL, hints;

	// Inicializa Winsock
	resultado = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (resultado != 0) {
		std::cout<<"WSAStartup fallo con el error: " << resultado<<"\n";
		exit(1);
	}

	// Pone información de la dirección
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	//protocolo de conexión TCP
	hints.ai_protocol = IPPROTO_TCP;

	//resuelve la dirección del servidor y el puerto
	resultado = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);

	if (resultado != 0) {
		std::cout<<"getaddrinfo fallo con el error: " << resultado<<"\n";
		WSACleanup();
		exit(1);
	}

	// Intenta conectarse a una dirección hasta que una tiene éxito
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConectarSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);

		if (ConectarSocket == INVALID_SOCKET) {
			std::cout<<"socket fallo con el error "<< WSAGetLastError()<<"\n";
			WSACleanup();
			exit(1);
		}

		// Conecta al servidor.
		resultado = connect(ConectarSocket, ptr->ai_addr, (int) ptr->ai_addrlen);

		if (resultado == SOCKET_ERROR) {
			closesocket (ConectarSocket);
			ConectarSocket = INVALID_SOCKET;
			printf("El server esta caido... no se conecta");
		}
	}

	// no necesita mas información de dirección para el servidor
	freeaddrinfo(result);

	// si falla la conexión
	if (ConectarSocket == INVALID_SOCKET) {
		printf("Imposible conectar con el servidor!\n");
		WSACleanup();
		exit(1);
	}

	// setea al socket para que no sea bloqueante
	u_long iMode = 1;

	resultado = ioctlsocket(ConectarSocket, FIONBIO, &iMode);
	if (resultado == SOCKET_ERROR) {
		std::cout<<"ioctlsocket fallo con el error: "<< WSAGetLastError()<<"\n";
		closesocket (ConectarSocket);
		WSACleanup();
		exit(1);
	}

	 //Deshabilita nagle
	    char value = 1;
	    setsockopt( ConectarSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );
}

int RedCliente::recibirPaquetes(char *recvbuf)
{
    resultado = ServiciosRed::recibirMensaje(ConectarSocket, recvbuf, MAX_PACKET_SIZE);

    if ( resultado == 0 )
    {
        printf("Connection closed\n");
        closesocket(ConectarSocket);
        WSACleanup();
        exit(1);
    }

    return resultado;
}


RedCliente::~RedCliente() {
	// TODO Auto-generated destructor stub
}

