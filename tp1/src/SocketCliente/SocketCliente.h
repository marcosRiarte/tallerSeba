#ifndef SOCKET_H_
#define SOCKET_H_

class Socket {

protected:
	int fd;
	bool valido;

private:
	Socket(int fd);
	Socket(const Socket& original);

public:
	Socket();
	virtual ~Socket();
	//int conectar(const std::string &host,unsigned int port);
	int escuchar(unsigned int port,unsigned int numClientesEspera);
	int cerrar();
	int enviar(char* stream,unsigned int size);
	int recibir(char* stream,unsigned int size);
	Socket* aceptar();
	bool es_valido();

};

#endif /* SOCKET_H_ */
