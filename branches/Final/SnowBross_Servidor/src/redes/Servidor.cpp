#include <exception>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Servidor.h"
#include "Paquetes.h"
#include "../Constantes.h"

WSADATA Servidor::wsa;
SOCKET Servidor::sockfd;
unsigned int Servidor::conexionesEstablecidas = 0;
SOCKET Servidor::sock[MAX_CANTIDAD_CONEXIONES];
struct sockaddr_in Servidor::local;
int Servidor::len;


void Servidor::iniciar(unsigned int cantidadConexiones) throw (Servidor_Excepcion){
	//Inicializamos
	WSAStartup(MAKEWORD(2, 0), &wsa);

	//Creamos el socket
	loguer->loguear("Creando el socket...", Log::LOG_DEB);
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0) {
		throw Servidor_Excepcion("No se pudo crear el socket del servidor");
	}
	loguer->loguear("Se creo el socket", Log::LOG_DEB);

	//defnimos dirección por defecto, ipv4 y el puerto
	memset((char *)&local,0, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(PUERTO);

	//asociamos el socket a la direccion
	loguer->loguear("Asociando socket a la direccion del servidor...", Log::LOG_DEB);
	if (bind(sockfd, (SOCKADDR*) &local, sizeof(local)) < 0) {
		throw Servidor_Excepcion("No se pudo associar el socket a la direccion del servidor");
	}
	loguer->loguear("Se asocio el socket a la direccion del servidor...", Log::LOG_DEB);

	//ponemos el socket a la escucha
	if (listen(sockfd, cantidadConexiones) < 0) {
		throw Servidor_Excepcion("No se pudo poner el socket del servidor a la escucha.");
	}
	loguer->loguear("Escuchando...", Log::LOG_DEB);

	//hay una conexión entrante y la aceptamos
	len = sizeof(struct sockaddr);
	for (unsigned i = 0; i < cantidadConexiones; i++){
		sock[conexionesEstablecidas] = accept(sockfd, (sockaddr*) &local, &len);
		if (sock[conexionesEstablecidas] < 0){
			throw Servidor_Excepcion("Fallo el intento de conexion");
		}
		conexionesEstablecidas++;
		loguer->loguear("Se estableció una conexion!!", Log::LOG_DEB);
	}
	loguer->loguear("Se establecieron todas las conexiones.", Log::LOG_DEB);
}

void Servidor::enviar(PaqueteACliente p) {
/*
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
*/
}

PaqueteAServidor Servidor::recibir() {
	PaqueteAServidor paquete;
/*	char buffer[sizeof(PaqueteAServidor)];
	int bytesRecibidos = 0;
	while ((bytesRecibidos != -1) && (bytesRecibidos != sizeof(PaqueteAServidor))) {
		bytesRecibidos = recv(sock, buffer, sizeof(PaqueteAServidor), 0);
	}
	paquete.deserialize(buffer);
*/
	return paquete;
}

Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}

