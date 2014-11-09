#include <iostream>
#include <string>

#include "Cliente.h"
#include "../Constantes.h"

WSADATA Cliente::wsa;
SOCKET Cliente::sock;
struct hostent* Cliente::host;
struct sockaddr_in Cliente::direc;

void Cliente::iniciar() throw (Cliente_Excepcion){
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
	loguer->loguear("Creando el socket...", Log::LOG_DEB);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		throw Cliente_Excepcion("No se pudo crear el socket.");
	}
	loguer->loguear("Se creo el socket", Log::LOG_DEB);

	//Definimos la dirección a conectar que hemos recibido desde el gethostbyname
	//y decimos que el puerto al que deberá conectar es el 9999 con el protocolo ipv4
	direc.sin_family = AF_INET;
	//Se utiliza htons por un tema de bigendian/littlendian
	direc.sin_port = htons(9999);
	direc.sin_addr = *((struct in_addr *) host->h_addr);
	memset(direc.sin_zero, 0, 8);

	//Intentamos establecer la conexión
	loguer->loguear("Conectandose...", Log::LOG_DEB);
	int conex = connect(sock, (sockaddr *) &direc, sizeof(sockaddr));
	if (conex < 0) {
		throw Cliente_Excepcion("No se pudo establecer la conexion.");
	}
	loguer->loguear("Se establecio la conexion!!", Log::LOG_DEB);
}

PaqueteACliente Cliente::recibir() throw (Cliente_Excepcion){
	char buffer[sizeof(PaqueteACliente)];
	unsigned int bytesRecibidos = 0;
	while ((bytesRecibidos >= 0) && (bytesRecibidos < sizeof(PaqueteACliente))){
		bytesRecibidos = recv(sock, buffer, sizeof(PaqueteACliente), 0);
	}
	if(bytesRecibidos < 0)
		throw Cliente_Excepcion("Fallo la recepcion del paquete. Se perdió la conexion.");
	PaqueteACliente paquete;
	paquete.deserialize(buffer);
	return paquete;
}

void Cliente::enviar(PaqueteAServidor p) throw (Cliente_Excepcion){
	char buffer[sizeof(PaqueteAServidor)];
	p.serialize(buffer);
	int bytesEnviados = send(sock, buffer, sizeof(PaqueteAServidor), 0);
	if (bytesEnviados < 0) {
		throw Cliente_Excepcion("Error en el envio del paquete. Se perdio la conexion");
	}
	if (bytesEnviados == sizeof(PaqueteAServidor))
		loguer->loguear("Se envio un paquete al servidor", Log::LOG_DEB);
	else
		loguer->loguear("Se envio un paquete a medias??", Log::LOG_WAR);
}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}
