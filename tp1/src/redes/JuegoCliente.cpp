/*
 * JuegoCliente.cpp
 *
 *  Created on: 27/10/2014
 *      Author: Seba
 */

#include "JuegoCliente.h"
#include <string>
#include <iostream>

JuegoCliente::JuegoCliente() {
	red = new RedCliente();
	// enviar init packet
	    const unsigned int packet_size = sizeof(Packet);
	    char packet_data[packet_size];

	    Packet packet;
	    packet.packet_type = INIT_CONNECTION;

	    packet.serialize(packet_data);

	    ServiciosRed::enviarMensaje(red->ConectarSocket, packet_data, packet_size);


}

void JuegoCliente::enviarPaquetesAccion(){
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = ACTION_EVENT;

    packet.serialize(packet_data);

    ServiciosRed::enviarMensaje(red->ConectarSocket, packet_data, packet_size);
}

void JuegoCliente::actualizar()
{
    Packet packet;
    int data_length = red->recibirPaquetes(network_data);

    if (data_length <= 0)
    {
        //no data recieved
        return;
    }

    int i = 0;
    while (i < (int)data_length)
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(Packet);

        switch (packet.packet_type) {

            case ACTION_EVENT:

                std::cout<<"el cliente recibió el paquete de accion del servidor"<<"\n";

                enviarPaquetesAccion();

                break;

            default:

                printf("error in packet types\n");

                break;
        }
    }
}

JuegoCliente::~JuegoCliente() {
	// TODO Auto-generated destructor stub
}

