#include "JuegoServidor.h"
#include <string>
#include <windows.h>
unsigned int JuegoServidor::id_cliente;

JuegoServidor::JuegoServidor() {
    // id's para asignar clientes a nuestra tabla
	id_cliente = 0;

	  // establecer la red del servidor a la escucha
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
    recibirDeClientes();
}

void JuegoServidor::recibirDeClientes()
{
    Packet packet;

    // go through all clients
    std::map<unsigned int, SOCKET>::iterator iter;

    for(iter = red->sesiones.begin(); iter != red->sesiones.end(); iter++)
    {
        // get data for that client
        int data_length = red->recibirDatos(iter->first, network_data);

        if (data_length <= 0)
        {
            //no data recieved
            continue;
        }

        int i = 0;
        while (i < data_length)
        {
            packet.deserialize(&(network_data[i]));
            i += sizeof(Packet);

            switch (packet.packet_type) {

                case INIT_CONNECTION:

                    std::cout<<"el servidor recibió el paquete init del cliente"<<"\n";
                    enviarPaquetesAccion();
                    //config->setPersonajes();
                    break;

                case ACTION_EVENT:

                	 std::cout<<"el servidor recibió el paquete de accion del cliente"<<"\n";
                     enviarPaquetesAccion();
                    break;

                default:

               	 std::cout<<"error del tipo de paquete"<<"\n";


                break;
            }
        }
    }
}

void JuegoServidor::enviarPaquetesAccion()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

    packet.serialize(packet_data);

    red->enviarATodos(packet_data,packet_size);
}


