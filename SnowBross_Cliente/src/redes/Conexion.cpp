#include "Conexion.h"
#include <iostream>
#include <string>

Conexion::Conexion() {
	//Inicializamos
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//resolvemos el nombre de dominio localhost, esto se resolverá a 127.0.0.1
	host = gethostbyname("localhost");

	/**
	 * creamos el socket:
	 * 	- AF_INET define un protocolo ipv4. (relacionado con el tipo de Ip's que se utilizan).
	 * 	- SOCK_STREAM define el tipo de paquetes para tcp.
	 * 	- IPPROTOTCP define el protocolo tcp.
	 */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == -1) {
		std::cout << "Error al crear el socket";
		throw;
	}

	//Definimos la dirección a conectar que hemos recibido desde el gethostbyname
	//y decimos que el puerto al que deberá conectar es el 9999 con el protocolo ipv4
	direc.sin_family = AF_INET;
	//Se utiliza htons por un tema de bigendian/littlendian
	direc.sin_port = htons(9999);
	direc.sin_addr = *((struct in_addr *) host->h_addr);
	memset(direc.sin_zero, 0, 8);

	//Intentamos establecer la conexión
	int conex = connect(sock, (sockaddr *) &direc, sizeof(sockaddr));
	if (conex == -1) {
		std::cout << "No se ha podido conectar\n";
		throw;
	}

	std::cout << "Se pudo establecer la conexion\n";
}

PaqueteACliente Conexion::recibir(){
	char buffer[sizeof(PaqueteACliente)];
	bytesRecibidos = 0;
	while ((bytesRecibidos != -1) && (bytesRecibidos != sizeof(PaqueteACliente))){
		bytesRecibidos = recv(sock, buffer, sizeof(PaqueteACliente), 0);
	}
	paquete.deserialize(buffer);
	return paquete;
}

Conexion::~Conexion() {
	// TODO Auto-generated destructor stub
}
