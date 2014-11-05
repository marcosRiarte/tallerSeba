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
        std::cout<<"el cliente "<< id_cliente << " se conect� al servidor"<<"\n";
        id_cliente++;
    }
    recibirDeClientes();
}

void JuegoServidor::recibirDeClientes()
{
    Packet packet;

    // recorre todos los clientes
    std::map<unsigned int, SOCKET>::iterator iter;

    for(iter = red->sesiones.begin(); iter != red->sesiones.end(); iter++)
    {
        // toma los datos del cliente
        int data_length = red->recibirDatos(iter->first, network_data);

        if (data_length <= 0)
        {
            //no recibi� ning�n dato
            continue;
        }

        int i = 0;
        while (i < data_length)
        {
            packet.deserialize(&(network_data[i]));
            i += sizeof(Packet);

            switch (packet.packet_type) {

                case INIT_CONNECTION:

                    std::cout<<"el servidor recibi� el paquete init del cliente"<<"\n";
                    enviarPaquetesAccion();
                    //config->setPersonajes();
                    break;

                case ACTION_EVENT:

                	 std::cout<<"el servidor recibi� el paquete de accion del cliente"<<"\n";
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
	FILE *pf;
	int fsize;
	char buffer[10000];

	pf = fopen("prueba.json", "rb");
	if (pf == NULL) {
		printf("archivo no encontrado!\n");
	} else {
		printf("archivo encontrado %s\n", "prueba.json");

		fseek(pf, 0, SEEK_END);
		fsize = ftell(pf);
		rewind(pf);

		std::cout<<"El archivo contiene "<<fsize<<" bytes!\n";
		printf("Enviando el archivo...\n");
	}


		// Leer los datos en buffer.
		int bytes_leidos = fread(buffer, 1, sizeof(buffer), pf);
		if (bytes_leidos == 0) // Terminamos de leer del archivo


		if (bytes_leidos < 0) {
			printf("ERROR leyendo el archivo\n");
		}

		if (bytes_leidos > 0) {
			red->enviarATodos(buffer,bytes_leidos);
		}

}


