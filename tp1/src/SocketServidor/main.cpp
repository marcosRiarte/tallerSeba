
#define TAM 1000

#include "SocketServidor.h"
#include "ThreadServidor.h"
#include <iostream>
#include <errno.h>

class Receptor: public ThreadCliente{

private:
	Socket* sock;
public:
	Receptor(Socket* sock){this->sock = sock;}
	virtual ~Receptor(){}
	void* run(){

		int cantidad;
		std::string buffer;
		char bufferTemp[1000];
		memset(bufferTemp,0,1000);
		while(this->sock->es_valido()){
			if( (cantidad = this->sock->recibir(bufferTemp, 999)) > 0){
				bufferTemp[cantidad] = '\0';
				buffer = bufferTemp;
				std::cout<<"\nReciev: "<<buffer<<std::endl;
			}
		}
		return NULL;
	}
};

/*
int main(int argc, char **argv) {
		Socket conexion;
		Receptor reci(&conexion);
		int i,tam;
		char buffer[TAM];
		conexion.conectar(argv[1],atoi(argv[2]));
		reci.ejecutar();
		std::cout << "Servidor: " << strerror(errno) << std::endl;
		for(i=0; i<10;i++){
			bzero(buffer,TAM);
			std::cout<<"Msj: ";
			std::cin>>buffer;
			tam = strlen(buffer);
			std::cout << "Buffer: " <<buffer<<" Tam: "<<tam<< std::endl;
			buffer[tam]='\0';
			conexion.enviar(buffer,tam);
			std::cout << "Send: " << strerror(errno) << std::endl;
			std::cout<<std::endl;
		}
		conexion.cerrar();
		reci.detectar_bloqueo();
	}
*/
