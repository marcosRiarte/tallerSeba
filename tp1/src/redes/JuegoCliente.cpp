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
    char mensaje_cliente[10000]="";
    while((red->recibirPaquetes(mensaje_cliente)) < 0 ){
    }
 }


JuegoCliente::~JuegoCliente() {
	// TODO Auto-generated destructor stub
}

