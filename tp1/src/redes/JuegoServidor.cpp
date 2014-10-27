#include "JuegoServidor.h"
#include <string>
#include <iostream>
unsigned int JuegoServidor::id_cliente;

JuegoServidor::JuegoServidor() {
    // id's para asignar clientes a nuestra tabla
	id_cliente = 0;

    // set up the server network to listen
    red = new RedServidor();
}

JuegoServidor::~JuegoServidor() {

}

void JuegoServidor::actualizar() {
    // tomar nuevos clientes
    if(red->aceptarCliente(id_cliente))
    {
        std::cout<<"el cliente "<< id_cliente << " se conectó al servidor"<<"\n";

        id_cliente++;
    }
}

