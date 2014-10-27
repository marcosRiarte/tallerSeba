/*
 * RedServidor.cpp
 *
 *  Created on: 27/10/2014
 *      Author: Seba
 */

#include "RedServidor.h"
#include <string>
#include <iostream>

RedServidor::RedServidor() {

	// crear el objeto WSADATA
	WSADATA wsaData;

	// nuestros sockets para el servidor
	SocketEscuchar = INVALID_SOCKET;
	SocketCliente = INVALID_SOCKET;

	// informaci�n de direcciones para la escucha del servidor
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Inicializa Winsock
	resultado = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (resultado != 0) {
		std::cout<<"WSAStartup fall� con el error: "<<resultado<<"\n";
		exit(1);
	}

	// Setea la informaci�n de la direcci�n
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

    // Protocolo de conexi�n TCP
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// resuelve la direcci�n del servidor y el puerto
	resultado = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

	if (resultado != 0) {
		std::cout<<"getaddrinfo fall� con el error: "<<resultado<<"\n";
		WSACleanup();
		exit(1);
	}

	// Crea un socket para conectar con el servidor
	SocketEscuchar = socket(result->ai_family, result->ai_socktype,
			result->ai_protocol);

	if (SocketEscuchar == INVALID_SOCKET) {
		std::cout<<"socket fall� con el error: "<< WSAGetLastError()<<"\n";
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	// Establece el socket como no bloqueante
	u_long iMode = 1;
	resultado = ioctlsocket(SocketEscuchar, FIONBIO, &iMode);

	if (resultado == SOCKET_ERROR) {
		std::cout<<"ioctlsocket fall� con el error: "<< WSAGetLastError()<<"\n";
		closesocket (SocketEscuchar);
		WSACleanup();
		exit(1);
	}


	// Establece el socket de escucha TCP
	resultado = bind(SocketEscuchar, result->ai_addr, (int) result->ai_addrlen);

	if (resultado == SOCKET_ERROR) {
		std::cout<<"bind fall� con el error: "<< WSAGetLastError()<<"\n";
		freeaddrinfo(result);
		closesocket (SocketEscuchar);
		WSACleanup();
		exit(1);
	}

	// Se elimina la informaci�n que ya no es necesaria
	freeaddrinfo(result);

	// Comienza la escucha para nuevos clientes que se quieran conectar
	resultado = listen(SocketEscuchar, SOMAXCONN);

	if (resultado == SOCKET_ERROR) {
		std::cout<<"listen fall� con el error: "<< WSAGetLastError()<<"\n";
		closesocket (SocketEscuchar);
		WSACleanup();
		exit(1);
	}
}

// acepta nuevas conexiones
bool RedServidor::aceptarCliente(unsigned int & id)
{
    // si el cliente esta esperando, acepta la conexi�n y crea el socket
    SocketCliente = accept(SocketEscuchar,nullptr,nullptr);

    if (SocketCliente != INVALID_SOCKET)
    {
        //Deshabilita el nagle en la conexi�n del cliente
        char value = 1;
        setsockopt( SocketCliente, IPPROTO_TCP, TCP_NODELAY, &value, sizeof( value ) );

        // inserta un nuevo cliente en la tabla de id de sesiones
        sesiones.insert( std::pair<unsigned int, SOCKET>(id, SocketCliente) );

        return 0;
    }
        return 1;
}

RedServidor::~RedServidor() {
	// TODO Auto-generated destructor stub
}

