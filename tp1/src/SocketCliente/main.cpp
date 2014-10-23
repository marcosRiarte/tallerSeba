/*
 * main.cpp
 *
 *  Created on: 08/05/2009
 *      Author: ale
 */
#define TAM 1000

#include "SocketServidor.h"
#include "ThreadServidor.h"
#include <iostream>
#include <errno.h>
#include <cstring>
//#include <arpa/inet.h>

/*
class Reciver: public Thread{

private:
	Socket* sock;
public:
	Reciver(Socket* cliente){this->sock = cliente;}
	virtual ~Reciver(){}


	void printHexa(char* buffer, int tam){
		for(int i = 0; i<tam; i++){
			std::cout<<std::ios::hex<<buffer[i]<<" ";
		}
		std::cout<<std::endl;
	}

	bool recvMsj(char** buffer,int& length){
		int temp=0;
		int cantidad = sock->receiveExact((char*) &temp,4); //TODO RE IMPORTNATE!!ver que el receive llene el buffer socket->receive no testeado!!
		if (cantidad > 0) {
			length = ntohl(temp);
			std::cout<<length<<std::endl;
			*buffer = new char[length];
			cantidad = sock->receive(*buffer, length);
			if (cantidad > 0) {
				printHexa(*buffer,cantidad);
				return true;
			}
			delete[] (*buffer);
			buffer = NULL;
		}
		return false;
	}

	void* run(){
		std::string buffer;
		char* bufferTemp;
		while(sock->is_valid()){
			int longitud =0;
			if( recvMsj(&bufferTemp,longitud)){

			}else{
				sock->close();
			}
		}
		return NULL;
	}
};




int main(int argc, char **argv) {
		Socket conexion;
		int i,tam;
		char buffer[TAM];

		conexion.listen(9999,1);
		std::cout << "Servidor Listen: " << strerror(errno) << std::endl;
		Socket* cliente = conexion.accept();
		std::cout << "Servidor Accept : " << strerror(errno) << std::endl;
		Reciver reci(cliente);
		reci.execute();
		for(i=0; i<10;i++){
			bzero(buffer,TAM);
			std::cout<<"Msj: ";
			std::cin>>buffer;
			tam = strlen(buffer);
			std::cout << "Buffer: " <<buffer<<" Tam: "<<tam<< std::endl;
			buffer[tam]='\0';
			cliente->send(buffer,tam);
			std::cout << "Send: " << strerror(errno) << std::endl;
			std::cout<<std::endl;
		}
		conexion.close();
		reci.join();
		delete cliente;
	}

*/
