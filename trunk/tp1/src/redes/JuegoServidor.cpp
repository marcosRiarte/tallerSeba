#include "JuegoServidor.h"
#include <string>

#include "../vistas/Pantalla.h"
#include "../escenario/Escenario.h"
#include "../parseo/Config.h"
#include "../Constantes.h"
#include "../controlador/Controlador.h"

#include <windows.h>

// Estructura del modelo
struct MVC {
	Escenario* escenario;
	Pantalla* pantalla;
	Config* config;
};

// Momentos de la ejecucion
MVC* creacionDelModelo(const char*) throw (MVC_Excepcion);
int gameLoop(MVC*);
void terminar(MVC*);

unsigned int JuegoServidor::id_cliente;

JuegoServidor::JuegoServidor() {
    // id's para asignar clientes a nuestra tabla
	id_cliente = 0;

	int fin = REINICIAR;
		while (FIN_DEL_JUEGO != fin) {
			try {
				MVC* mvc = creacionDelModelo("prueba.json");
				fin = gameLoop(mvc);
				terminar(mvc);
			} catch (MVC_Excepcion& ex) {
				std::cout << ex.what() << "\n";
				std::cout << "Revisar log de errores" << "\n";
				exit(1);
			}
		}

	  // establecer la red del servidor a la escucha
	    red = new RedServidor();


}

// Crea todas las partes del modelo
MVC* creacionDelModelo(const char* direccionDeLaConfiguracion) throw (MVC_Excepcion) {
	MVC* mvc = new MVC;
	char msg[1000];

	//Se parsea el archivo Json
	try {
		std::string asd = "prueba.json";
		mvc->config = new Config(asd);

	} catch (Config_Excepcion&) {
		throw MVC_Excepcion("No se pudo parsear el archivo .json");
	}

	//Se loguea la creación de objetos
	snprintf(msg, 1000, "Se parsearon: %d objetos",	mvc->config->getObjetos().size());
	loguer->loguear(msg, Log::LOG_DEB);

	//Se crea el escenario
	mvc->escenario = new Escenario(mvc->config);

	//Se loguea la creación del escenario
	snprintf(msg, 1000,
			"Se creo la física Box2D con ancho: %d unidades, alto %d unidades y %d objetos",
			mvc->config->getAncho(),
			mvc->config->getAlto(),
			mvc->config->getObjetos().size());
	loguer->loguear(msg, Log::LOG_DEB);

	//Se inicializa SDL
	Controlador::iniciarSDL();

	//Se crea la pantalla
		try {
			mvc->pantalla = new Pantalla(mvc->config);
		} catch (SDL_Excepcion&) {
			throw MVC_Excepcion("No se pudo crear la pantalla \n");
		}

		//Se loguea la creación de pantalla
		snprintf(msg, 1000,
				"Se creo la pantalla con ancho: %d unidades y alto %d unidades",
				mvc->pantalla->getAncho(), mvc->pantalla->getAlto());
		loguer->loguear(msg, Log::LOG_DEB);

	return mvc;
}

// Ejecuta el modelo
int gameLoop(MVC* mvc) {
	std::vector<Evento> listaDeEventos = std::vector<Evento>();
	listaDeEventos = std::vector<Evento>();
	int fin = CONTINUAR;
	while (FIN_DEL_JUEGO != fin && REINICIAR != fin) {
		// Responsabilidades> ...
		fin = Controlador::cambiar(&listaDeEventos);
		mvc->escenario->cambiar(&listaDeEventos);
		mvc->pantalla->cambiar(&listaDeEventos);
		SDL_Delay(10);
	}

	return fin;
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
   // recibirDeClientes();
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

// Libera la memoria
void terminar(MVC* mvc){
	delete mvc->escenario;
	delete mvc->pantalla;
	delete mvc->config;
	delete mvc;
	SDL_Quit();
}

