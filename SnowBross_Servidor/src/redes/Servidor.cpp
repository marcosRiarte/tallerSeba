#include "Servidor.h"
#include <exception>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Paquetes.h"

WSADATA Servidor::wsa;
SOCKET Servidor::sock;
struct sockaddr_in Servidor::local;
int Servidor::len;


void Servidor::iniciar() {
	//Inicializamos
	WSAStartup(MAKEWORD(2, 0), &wsa);

	//Creamos el socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1) {
		//TODO - Crear excepcion!!!
		throw;
	}

	//defnimos dirección por defecto, ipv4 y el puerto 9999
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(9999);

	//asociamos el socket al puerto
	if (bind(sock, (SOCKADDR*) &local, sizeof(local)) == -1) {
		//TODO - Crear excepcion!!!
		throw;
	}

	//ponemos el socket a la escucha
	if (listen(sock, 1) == -1) {
		//TODO - Crear excepcion!!!
		throw;
	}

	//hay una conexión entrante y la aceptamos
	len = sizeof(struct sockaddr);
	sock = accept(sock, (sockaddr*) &local, &len);
}

void Servidor::enviar(PaqueteACliente p) {

	char buffer [sizeof(PaqueteACliente)];

	p.serialize(buffer);

	int bytesEnviados = send(sock, buffer, sizeof(PaqueteACliente), 0);

	if (bytesEnviados == -1){
		std::cout << "Fallo el envio.";
		throw;
	}

	if (bytesEnviados == sizeof(PaqueteACliente))
		std::cout << "Envio exitoso.";
	else
		std::cout << "Se enviaron: " << bytesEnviados << "bytes, RARO!";
}

PaqueteAServidor Servidor::recibir() {
	PaqueteAServidor paquete;
	char buffer[sizeof(PaqueteAServidor)];
	int bytesRecibidos = 0;
	while ((bytesRecibidos != -1) && (bytesRecibidos != sizeof(PaqueteAServidor))) {
		bytesRecibidos = recv(sock, buffer, sizeof(PaqueteAServidor), 0);
	}
	paquete.deserialize(buffer);
	return paquete;
}

Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}

